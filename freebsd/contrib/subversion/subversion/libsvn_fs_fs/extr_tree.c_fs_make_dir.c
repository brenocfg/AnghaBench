#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int txn_flags; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {int /*<<< orphan*/  entry; struct TYPE_13__* parent; scalar_t__ node; } ;
typedef  TYPE_2__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_FS__ALREADY_EXISTS (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_newline (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dag_node_cache_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_1__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_path (TYPE_2__**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_path_last_optional ; 
 int /*<<< orphan*/  parent_path_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * root_txn_id (TYPE_1__*) ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__allow_locked_operation (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_make_dir (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_path_change_add ; 
 int /*<<< orphan*/  svn_node_dir ; 

__attribute__((used)) static svn_error_t *
fs_make_dir(svn_fs_root_t *root,
            const char *path,
            apr_pool_t *pool)
{
  parent_path_t *parent_path;
  dag_node_t *sub_dir;
  const svn_fs_fs__id_part_t *txn_id = root_txn_id(root);

  SVN_ERR(check_newline(path, pool));

  path = svn_fs__canonicalize_abspath(path, pool);
  SVN_ERR(open_path(&parent_path, root, path, open_path_last_optional,
                    TRUE, pool));

  /* Check (recursively) to see if some lock is 'reserving' a path at
     that location, or even some child-path; if so, check that we can
     use it. */
  if (root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_fs__allow_locked_operation(path, root->fs, TRUE, FALSE,
                                              pool));

  /* If there's already a sub-directory by that name, complain.  This
     also catches the case of trying to make a subdirectory named `/'.  */
  if (parent_path->node)
    return SVN_FS__ALREADY_EXISTS(root, path);

  /* Create the subdirectory.  */
  SVN_ERR(make_path_mutable(root, parent_path->parent, path, pool));
  SVN_ERR(svn_fs_fs__dag_make_dir(&sub_dir,
                                  parent_path->parent->node,
                                  parent_path_path(parent_path->parent,
                                                   pool),
                                  parent_path->entry,
                                  txn_id,
                                  pool));

  /* Add this directory to the path cache. */
  SVN_ERR(dag_node_cache_set(root, parent_path_path(parent_path, pool),
                             sub_dir, pool));

  /* Make a record of this modification in the changes table. */
  return add_change(root->fs, txn_id, path, svn_fs_fs__dag_get_id(sub_dir),
                    svn_fs_path_change_add, FALSE, FALSE, FALSE,
                    svn_node_dir, SVN_INVALID_REVNUM, NULL, pool);
}