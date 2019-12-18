#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_6__ {scalar_t__ revision; scalar_t__ item_index; int /*<<< orphan*/  md5_digest; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_1__ representation_t ;
struct TYPE_7__ {int /*<<< orphan*/  id; TYPE_1__* prop_rep; } ;
typedef  TYPE_2__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_fs__prop_lists_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__id_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_used (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__prop_rep_equal(svn_boolean_t *equal,
                          svn_fs_t *fs,
                          node_revision_t *a,
                          node_revision_t *b,
                          apr_pool_t *scratch_pool)
{
  representation_t *rep_a = a->prop_rep;
  representation_t *rep_b = b->prop_rep;
  apr_hash_t *proplist_a;
  apr_hash_t *proplist_b;

  /* Mainly for a==b==NULL */
  if (rep_a == rep_b)
    {
      *equal = TRUE;
      return SVN_NO_ERROR;
    }

  /* Committed property lists can be compared quickly */
  if (   rep_a && rep_b
      && !svn_fs_fs__id_txn_used(&rep_a->txn_id)
      && !svn_fs_fs__id_txn_used(&rep_b->txn_id))
    {
      /* Same representation? */
      if (   (rep_a->revision == rep_b->revision)
          && (rep_a->item_index == rep_b->item_index))
        {
          *equal = TRUE;
          return SVN_NO_ERROR;
        }

      /* Known different content? MD5 must be given. */
      if (memcmp(rep_a->md5_digest, rep_b->md5_digest,
                 sizeof(rep_a->md5_digest)))
        {
          *equal = FALSE;
          return SVN_NO_ERROR;
        }
    }

  /* Same path in same txn?
   *
   * For committed reps, IDs cannot be the same here b/c we already know
   * that they point to different representations. */
  if (svn_fs_fs__id_eq(a->id, b->id))
    {
      *equal = TRUE;
      return SVN_NO_ERROR;
    }

  /* At least one of the reps has been modified in a txn.
     Fetch and compare them. */
  SVN_ERR(svn_fs_fs__get_proplist(&proplist_a, fs, a, scratch_pool));
  SVN_ERR(svn_fs_fs__get_proplist(&proplist_b, fs, b, scratch_pool));

  *equal = svn_fs__prop_lists_equal(proplist_a, proplist_b, scratch_pool);
  return SVN_NO_ERROR;
}