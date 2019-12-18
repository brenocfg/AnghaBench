#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_15__ {int expanded_size; } ;
typedef  TYPE_2__ representation_t ;
struct TYPE_16__ {int predecessor_count; TYPE_2__* data_rep; TYPE_2__* prop_rep; int /*<<< orphan*/  predecessor_id; } ;
typedef  TYPE_3__ node_revision_t ;
struct TYPE_17__ {scalar_t__ max_linear_deltification; scalar_t__ max_deltification_walk; } ;
typedef  TYPE_4__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  shards_spanned (int*,TYPE_1__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__get_node_revision (TYPE_3__**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__rep_chain_length (int*,int*,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
choose_delta_base(representation_t **rep,
                  svn_fs_t *fs,
                  node_revision_t *noderev,
                  svn_boolean_t props,
                  apr_pool_t *pool)
{
  /* The zero-based index (counting from the "oldest" end), along NODEREVs line
   * predecessors, of the node-rev we will use as delta base. */
  int count;
  /* The length of the linear part of a delta chain.  (Delta chains use
   * skip-delta bits for the high-order bits and are linear in the low-order
   * bits.) */
  int walk;
  node_revision_t *base;
  fs_fs_data_t *ffd = fs->fsap_data;
  apr_pool_t *iterpool;

  /* If we have no predecessors, or that one is empty, then use the empty
   * stream as a base. */
  if (! noderev->predecessor_count)
    {
      *rep = NULL;
      return SVN_NO_ERROR;
    }

  /* Flip the rightmost '1' bit of the predecessor count to determine
     which file rev (counting from 0) we want to use.  (To see why
     count & (count - 1) unsets the rightmost set bit, think about how
     you decrement a binary number.) */
  count = noderev->predecessor_count;
  count = count & (count - 1);

  /* Finding the delta base over a very long distance can become extremely
     expensive for very deep histories, possibly causing client timeouts etc.
     OTOH, this is a rare operation and its gains are minimal. Lets simply
     start deltification anew close every other 1000 changes or so.  */
  walk = noderev->predecessor_count - count;
  if (walk > (int)ffd->max_deltification_walk)
    {
      *rep = NULL;
      return SVN_NO_ERROR;
    }

  /* We use skip delta for limiting the number of delta operations
     along very long node histories.  Close to HEAD however, we create
     a linear history to minimize delta size.  */
  if (walk < (int)ffd->max_linear_deltification)
    {
      int shards;
      SVN_ERR(shards_spanned(&shards, fs, noderev, walk, pool));

      /* We also don't want the linear deltification to span more shards
         than if deltas we used in a simple skip-delta scheme. */
      if ((1 << (--shards)) <= walk)
        count = noderev->predecessor_count - 1;
    }

  /* Walk back a number of predecessors equal to the difference
     between count and the original predecessor count.  (For example,
     if noderev has ten predecessors and we want the eighth file rev,
     walk back two predecessors.) */
  base = noderev;
  iterpool = svn_pool_create(pool);
  while ((count++) < noderev->predecessor_count)
    {
      svn_pool_clear(iterpool);
      SVN_ERR(svn_fs_fs__get_node_revision(&base, fs,
                                           base->predecessor_id, pool,
                                           iterpool));
    }
  svn_pool_destroy(iterpool);

  /* return a suitable base representation */
  *rep = props ? base->prop_rep : base->data_rep;

  /* if we encountered a shared rep, its parent chain may be different
   * from the node-rev parent chain. */
  if (*rep)
    {
      int chain_length = 0;
      int shard_count = 0;

      /* Very short rep bases are simply not worth it as we are unlikely
       * to re-coup the deltification space overhead of 20+ bytes. */
      svn_filesize_t rep_size = (*rep)->expanded_size;
      if (rep_size < 64)
        {
          *rep = NULL;
          return SVN_NO_ERROR;
        }

      /* Check whether the length of the deltification chain is acceptable.
       * Otherwise, shared reps may form a non-skipping delta chain in
       * extreme cases. */
      SVN_ERR(svn_fs_fs__rep_chain_length(&chain_length, &shard_count,
                                          *rep, fs, pool));

      /* Some reasonable limit, depending on how acceptable longer linear
       * chains are in this repo.  Also, allow for some minimal chain. */
      if (chain_length >= 2 * (int)ffd->max_linear_deltification + 2)
        *rep = NULL;
      else
        /* To make it worth opening additional shards / pack files, we
         * require that the reps have a certain minimal size.  To deltify
         * against a rep in different shard, the lower limit is 512 bytes
         * and doubles with every extra shard to visit along the delta
         * chain. */
        if (   shard_count > 1
            && ((svn_filesize_t)128 << shard_count) >= rep_size)
          *rep = NULL;
    }

  return SVN_NO_ERROR;
}