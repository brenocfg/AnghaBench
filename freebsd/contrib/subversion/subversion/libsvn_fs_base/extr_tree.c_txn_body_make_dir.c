#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_17__ {char* txn; int txn_flags; int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct make_dir_args {char* path; TYPE_2__* root; } ;
struct TYPE_18__ {int /*<<< orphan*/  entry; TYPE_7__* parent; scalar_t__ node; } ;
typedef  TYPE_3__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_19__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_FS__ALREADY_EXISTS (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_2__*,TYPE_7__*,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_path (TYPE_3__**,TYPE_2__*,char const*,int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_path_last_optional ; 
 int /*<<< orphan*/  parent_path_path (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__allow_locked_operation (char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_make_dir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_add ; 

__attribute__((used)) static svn_error_t *
txn_body_make_dir(void *baton,
                  trail_t *trail)
{
  struct make_dir_args *args = baton;
  svn_fs_root_t *root = args->root;
  const char *path = args->path;
  parent_path_t *parent_path;
  dag_node_t *sub_dir;
  const char *txn_id = root->txn;

  SVN_ERR(open_path(&parent_path, root, path, open_path_last_optional,
                    txn_id, trail, trail->pool));

  /* If there's already a sub-directory by that name, complain.  This
     also catches the case of trying to make a subdirectory named `/'.  */
  if (parent_path->node)
    return SVN_FS__ALREADY_EXISTS(root, path);

  /* Check to see if some lock is 'reserving' a file-path or dir-path
     at that location, or even some child-path;  if so, check that we
     can use it. */
  if (args->root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    {
      SVN_ERR(svn_fs_base__allow_locked_operation(path, TRUE,
                                                  trail, trail->pool));
    }

  /* Create the subdirectory.  */
  SVN_ERR(make_path_mutable(root, parent_path->parent, path,
                            trail, trail->pool));
  SVN_ERR(svn_fs_base__dag_make_dir(&sub_dir,
                                    parent_path->parent->node,
                                    parent_path_path(parent_path->parent,
                                                     trail->pool),
                                    parent_path->entry,
                                    txn_id,
                                    trail, trail->pool));

  /* Make a record of this modification in the changes table. */
  return add_change(root->fs, txn_id, path,
                    svn_fs_base__dag_get_id(sub_dir),
                    svn_fs_path_change_add, FALSE, FALSE,
                    trail, trail->pool);
}