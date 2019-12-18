#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_13__ {TYPE_6__* parent; int /*<<< orphan*/  entry; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ svn_fs_x__dag_path_t ;
struct TYPE_14__ {int txn_flags; int /*<<< orphan*/  fs; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
struct TYPE_15__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_ROOT_DIR ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_FS__NOT_TXN (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  increment_mergeinfo_up_tree (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_path_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_delete ; 
 int /*<<< orphan*/  svn_fs_x__allow_locked_operation (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_mergeinfo_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__dag_node_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_path (TYPE_1__**,TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__invalidate_dag_cache (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__make_path_mutable (TYPE_2__*,TYPE_6__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__root_txn_id (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_delete_node(svn_fs_root_t *root,
              const char *path,
              apr_pool_t *scratch_pool)
{
  svn_fs_x__dag_path_t *dag_path;
  svn_fs_x__txn_id_t txn_id;
  apr_int64_t mergeinfo_count = 0;
  svn_node_kind_t kind;
  apr_pool_t *subpool = svn_pool_create(scratch_pool);

  if (! root->is_txn_root)
    return SVN_FS__NOT_TXN(root);

  txn_id = svn_fs_x__root_txn_id(root);
  SVN_ERR(svn_fs_x__get_dag_path(&dag_path, root, path, 0, TRUE, subpool,
                                 subpool));
  kind = svn_fs_x__dag_node_kind(dag_path->node);

  /* We can't remove the root of the filesystem.  */
  if (! dag_path->parent)
    return svn_error_create(SVN_ERR_FS_ROOT_DIR, NULL,
                            _("The root directory cannot be deleted"));

  /* Check to see if path (or any child thereof) is locked; if so,
     check that we can use the existing lock(s). */
  if (root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_x__allow_locked_operation(path, root->fs, TRUE, FALSE,
                                             subpool));

  /* Make the parent directory mutable, and do the deletion.  */
  SVN_ERR(svn_fs_x__make_path_mutable(root, dag_path->parent, path, subpool,
                                      subpool));
  mergeinfo_count = svn_fs_x__dag_get_mergeinfo_count(dag_path->node);
  SVN_ERR(svn_fs_x__dag_delete(dag_path->parent->node,
                               dag_path->entry,
                               txn_id, subpool));

  /* Remove this node and any children from the path cache. */
  svn_fs_x__invalidate_dag_cache(root, parent_path_path(dag_path, subpool));

  /* Update mergeinfo counts for parents */
  if (mergeinfo_count > 0)
    SVN_ERR(increment_mergeinfo_up_tree(dag_path->parent,
                                        -mergeinfo_count,
                                        subpool));

  /* Make a record of this modification in the changes table. */
  SVN_ERR(add_change(root->fs, txn_id, path,
                     svn_fs_path_change_delete, FALSE, FALSE, FALSE, kind,
                     SVN_INVALID_REVNUM, NULL, subpool));

  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}