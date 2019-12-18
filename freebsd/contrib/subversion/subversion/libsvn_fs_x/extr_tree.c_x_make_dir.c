#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_11__ {int /*<<< orphan*/  entry; TYPE_6__* parent; scalar_t__ node; } ;
typedef  TYPE_1__ svn_fs_x__dag_path_t ;
struct TYPE_12__ {int txn_flags; int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_FS__ALREADY_EXISTS (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_path_path (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_path_change_add ; 
 int /*<<< orphan*/  svn_fs_x__allow_locked_operation (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_make_dir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_path_last_optional ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_path (TYPE_1__**,TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__make_path_mutable (TYPE_2__*,TYPE_6__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__root_txn_id (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_x__update_dag_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_make_dir(svn_fs_root_t *root,
           const char *path,
           apr_pool_t *scratch_pool)
{
  svn_fs_x__dag_path_t *dag_path;
  dag_node_t *sub_dir;
  svn_fs_x__txn_id_t txn_id = svn_fs_x__root_txn_id(root);
  apr_pool_t *subpool = svn_pool_create(scratch_pool);

  SVN_ERR(svn_fs_x__get_dag_path(&dag_path, root, path,
                                 svn_fs_x__dag_path_last_optional,
                                 TRUE, subpool, subpool));

  /* Check (recursively) to see if some lock is 'reserving' a path at
     that location, or even some child-path; if so, check that we can
     use it. */
  if (root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_x__allow_locked_operation(path, root->fs, TRUE, FALSE,
                                             subpool));

  /* If there's already a sub-directory by that name, complain.  This
     also catches the case of trying to make a subdirectory named `/'.  */
  if (dag_path->node)
    return SVN_FS__ALREADY_EXISTS(root, path);

  /* Create the subdirectory.  */
  SVN_ERR(svn_fs_x__make_path_mutable(root, dag_path->parent, path, subpool,
                                      subpool));
  SVN_ERR(svn_fs_x__dag_make_dir(&sub_dir,
                                 dag_path->parent->node,
                                 parent_path_path(dag_path->parent,
                                                  subpool),
                                 dag_path->entry,
                                 txn_id,
                                 subpool, subpool));

  /* Add this directory to the path cache. */
  svn_fs_x__update_dag_cache(sub_dir);

  /* Make a record of this modification in the changes table. */
  SVN_ERR(add_change(root->fs, txn_id, path,
                     svn_fs_path_change_add, FALSE, FALSE, FALSE,
                     svn_node_dir, SVN_INVALID_REVNUM, NULL, subpool));

  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}