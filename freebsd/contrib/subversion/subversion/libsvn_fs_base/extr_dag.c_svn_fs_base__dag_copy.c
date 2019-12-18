#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_11__ {int predecessor_count; int /*<<< orphan*/  created_path; int /*<<< orphan*/  predecessor_id; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_kind_real ; 
 int /*<<< orphan*/  svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__add_txn_copy (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__create_successor (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_created_path (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_fs (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_id (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_set_entry (TYPE_2__*,char const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__id_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__rev_get_txn_id (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__create_copy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__reserve_copy_id (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__dag_copy(dag_node_t *to_node,
                      const char *entry,
                      dag_node_t *from_node,
                      svn_boolean_t preserve_history,
                      svn_revnum_t from_rev,
                      const char *from_path,
                      const char *txn_id,
                      trail_t *trail,
                      apr_pool_t *pool)
{
  const svn_fs_id_t *id;

  if (preserve_history)
    {
      node_revision_t *noderev;
      const char *copy_id;
      svn_fs_t *fs = svn_fs_base__dag_get_fs(from_node);
      const svn_fs_id_t *src_id = svn_fs_base__dag_get_id(from_node);
      const char *from_txn_id = NULL;

      /* Make a copy of the original node revision. */
      SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, fs, from_node->id,
                                            trail, pool));

      /* Reserve a copy ID for this new copy. */
      SVN_ERR(svn_fs_bdb__reserve_copy_id(&copy_id, fs, trail, pool));

      /* Create a successor with its predecessor pointing at the copy
         source. */
      noderev->predecessor_id = svn_fs_base__id_copy(src_id, pool);
      if (noderev->predecessor_count != -1)
        noderev->predecessor_count++;
      noderev->created_path = svn_fspath__join
        (svn_fs_base__dag_get_created_path(to_node), entry, pool);
      SVN_ERR(svn_fs_base__create_successor(&id, fs, src_id, noderev,
                                            copy_id, txn_id, trail, pool));

      /* Translate FROM_REV into a transaction ID. */
      SVN_ERR(svn_fs_base__rev_get_txn_id(&from_txn_id, fs, from_rev,
                                          trail, pool));

      /* Now that we've done the copy, we need to add the information
         about the copy to the `copies' table, using the COPY_ID we
         reserved above.  */
      SVN_ERR(svn_fs_bdb__create_copy
              (fs, copy_id,
               svn_fs__canonicalize_abspath(from_path, pool),
               from_txn_id, id, copy_kind_real, trail, pool));

      /* Finally, add the COPY_ID to the transaction's list of copies
         so that, if this transaction is aborted, the `copies' table
         entry we added above will be cleaned up. */
      SVN_ERR(svn_fs_base__add_txn_copy(fs, txn_id, copy_id, trail, pool));
    }
  else  /* don't preserve history */
    {
      id = svn_fs_base__dag_get_id(from_node);
    }

  /* Set the entry in to_node to the new id. */
  return svn_fs_base__dag_set_entry(to_node, entry, id, txn_id,
                                    trail, pool);
}