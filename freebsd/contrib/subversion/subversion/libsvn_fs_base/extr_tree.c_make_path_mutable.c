#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_7__ {char* txn; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {char* copy_src_path; int copy_inherit; int /*<<< orphan*/ * node; int /*<<< orphan*/  entry; struct TYPE_8__* parent; } ;
typedef  TYPE_2__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int copy_id_inherit_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
#define  copy_id_inherit_new 131 
#define  copy_id_inherit_parent 130 
#define  copy_id_inherit_self 129 
#define  copy_id_inherit_unknown 128 
 int /*<<< orphan*/  copy_kind_soft ; 
 int /*<<< orphan*/ * mutable_root_node (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* parent_path_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__add_txn_copy (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_base__dag_check_mutable (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_clone_child (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 char* svn_fs_base__id_copy_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_base__id_txn_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_fs_bdb__create_copy (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_bdb__reserve_copy_id (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
make_path_mutable(svn_fs_root_t *root,
                  parent_path_t *parent_path,
                  const char *error_path,
                  trail_t *trail,
                  apr_pool_t *pool)
{
  dag_node_t *cloned_node;
  const char *txn_id = root->txn;
  svn_fs_t *fs = root->fs;

  /* Is the node mutable already?  */
  if (svn_fs_base__dag_check_mutable(parent_path->node, txn_id))
    return SVN_NO_ERROR;

  /* Are we trying to clone the root, or somebody's child node?  */
  if (parent_path->parent)
    {
      const svn_fs_id_t *parent_id;
      const svn_fs_id_t *node_id = svn_fs_base__dag_get_id(parent_path->node);
      const char *copy_id = NULL;
      const char *copy_src_path = parent_path->copy_src_path;
      copy_id_inherit_t inherit = parent_path->copy_inherit;
      const char *clone_path;

      /* We're trying to clone somebody's child.  Make sure our parent
         is mutable.  */
      SVN_ERR(make_path_mutable(root, parent_path->parent,
                                error_path, trail, pool));

      switch (inherit)
        {
        case copy_id_inherit_parent:
          parent_id = svn_fs_base__dag_get_id(parent_path->parent->node);
          copy_id = svn_fs_base__id_copy_id(parent_id);
          break;

        case copy_id_inherit_new:
          SVN_ERR(svn_fs_bdb__reserve_copy_id(&copy_id, fs, trail, pool));
          break;

        case copy_id_inherit_self:
          copy_id = NULL;
          break;

        case copy_id_inherit_unknown:
        default:
          SVN_ERR_MALFUNCTION(); /* uh-oh -- somebody didn't calculate copy-ID
                      inheritance data. */
        }

      /* Now make this node mutable.  */
      clone_path = parent_path_path(parent_path->parent, pool);
      SVN_ERR(svn_fs_base__dag_clone_child(&cloned_node,
                                           parent_path->parent->node,
                                           clone_path,
                                           parent_path->entry,
                                           copy_id, txn_id,
                                           trail, pool));

      /* If we just created a brand new copy ID, we need to store a
         `copies' table entry for it, as well as a notation in the
         transaction that should this transaction be terminated, our
         new copy needs to be removed. */
      if (inherit == copy_id_inherit_new)
        {
          const svn_fs_id_t *new_node_id =
            svn_fs_base__dag_get_id(cloned_node);
          SVN_ERR(svn_fs_bdb__create_copy(fs, copy_id, copy_src_path,
                                          svn_fs_base__id_txn_id(node_id),
                                          new_node_id,
                                          copy_kind_soft, trail, pool));
          SVN_ERR(svn_fs_base__add_txn_copy(fs, txn_id, copy_id,
                                            trail, pool));
        }
    }
  else
    {
      /* We're trying to clone the root directory.  */
      SVN_ERR(mutable_root_node(&cloned_node, root, error_path, trail, pool));
    }

  /* Update the PARENT_PATH link to refer to the clone.  */
  parent_path->node = cloned_node;

  return SVN_NO_ERROR;
}