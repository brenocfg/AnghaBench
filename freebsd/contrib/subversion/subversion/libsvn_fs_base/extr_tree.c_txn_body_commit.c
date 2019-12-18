#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_16__ {char* id; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_3__ svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct commit_args {int /*<<< orphan*/  new_rev; TYPE_3__* txn; } ;
typedef  int /*<<< orphan*/  dag_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_TXN_OUT_OF_DATE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_check_mutable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_clone_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_commit_txn (int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_txn_base_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_txn_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__id_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_fs_base__id_unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__rev_get_root (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_locks (char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_commit(void *baton, trail_t *trail)
{
  struct commit_args *args = baton;

  svn_fs_txn_t *txn = args->txn;
  svn_fs_t *fs = txn->fs;
  const char *txn_name = txn->id;

  svn_revnum_t youngest_rev;
  const svn_fs_id_t *y_rev_root_id;
  dag_node_t *txn_base_root_node, *txn_root_node;

  /* Getting the youngest revision locks the revisions table until
     this trail is done. */
  SVN_ERR(svn_fs_bdb__youngest_rev(&youngest_rev, fs, trail, trail->pool));

  /* If the root of the youngest revision is the same as txn's base,
     then no further merging is necessary and we can commit. */
  SVN_ERR(svn_fs_base__rev_get_root(&y_rev_root_id, fs, youngest_rev,
                                    trail, trail->pool));
  SVN_ERR(svn_fs_base__dag_txn_base_root(&txn_base_root_node, fs, txn_name,
                                         trail, trail->pool));
  /* ### kff todo: it seems weird to grab the ID for one, and the node
     for the other.  We can certainly do the comparison we need, but
     it would be nice to grab the same type of information from the
     start, instead of having to transform one of them. */
  if (! svn_fs_base__id_eq(y_rev_root_id,
                           svn_fs_base__dag_get_id(txn_base_root_node)))
    {
      svn_string_t *id_str = svn_fs_base__id_unparse(y_rev_root_id,
                                                     trail->pool);
      return svn_error_createf
        (SVN_ERR_FS_TXN_OUT_OF_DATE, NULL,
         _("Transaction '%s' out-of-date with respect to revision '%s'"),
         txn_name, id_str->data);
    }

  /* Locks may have been added (or stolen) between the calling of
     previous svn_fs.h functions and svn_fs_commit_txn(), so we need
     to re-examine every changed-path in the txn and re-verify all
     discovered locks. */
  SVN_ERR(verify_locks(txn_name, trail, trail->pool));

  /* Ensure every txn has a mutable root as then the new revision will
     have a distinct root node-revision-id.  This is necessary as
     future transactions use the root node-revision-id as a proxy for
     the transaction base revision. */
  SVN_ERR(svn_fs_base__dag_txn_root(&txn_root_node, fs, txn_name,
                                    trail, trail->pool));
  if (!svn_fs_base__dag_check_mutable(txn_root_node, txn->id))
    {
      dag_node_t *clone;
      SVN_ERR(svn_fs_base__dag_clone_root(&clone, fs, txn->id,
                                          trail, trail->pool));
    }

  /* Else, commit the txn. */
  return svn_fs_base__dag_commit_txn(&(args->new_rev), txn, trail,
                                     trail->pool);
}