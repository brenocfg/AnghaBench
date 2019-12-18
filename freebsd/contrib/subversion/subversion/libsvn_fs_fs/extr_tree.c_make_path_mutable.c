#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_18__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_19__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_20__ {int copy_inherit; int /*<<< orphan*/ * node; int /*<<< orphan*/  entry; struct TYPE_20__* parent; } ;
typedef  TYPE_3__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int copy_id_inherit_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
#define  copy_id_inherit_new 131 
#define  copy_id_inherit_parent 130 
#define  copy_id_inherit_self 129 
#define  copy_id_inherit_unknown 128 
 int /*<<< orphan*/ * dag_node_cache_set (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_dag (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mutable_root_node (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 char* parent_path_path (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* root_txn_id (TYPE_1__*) ; 
 scalar_t__ svn_fs_fs__dag_check_mutable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_clone_child (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_get_copyroot (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_get_id (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_fs_fs__id_copy_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_node_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_part_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_fs__reserve_copy_id (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__revision_root (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
make_path_mutable(svn_fs_root_t *root,
                  parent_path_t *parent_path,
                  const char *error_path,
                  apr_pool_t *pool)
{
  dag_node_t *clone;
  const svn_fs_fs__id_part_t *txn_id = root_txn_id(root);

  /* Is the node mutable already?  */
  if (svn_fs_fs__dag_check_mutable(parent_path->node))
    return SVN_NO_ERROR;

  /* Are we trying to clone the root, or somebody's child node?  */
  if (parent_path->parent)
    {
      const svn_fs_id_t *parent_id, *child_id, *copyroot_id;
      svn_fs_fs__id_part_t copy_id = { SVN_INVALID_REVNUM, 0 };
      svn_fs_fs__id_part_t *copy_id_ptr = &copy_id;
      copy_id_inherit_t inherit = parent_path->copy_inherit;
      const char *clone_path, *copyroot_path;
      svn_revnum_t copyroot_rev;
      svn_boolean_t is_parent_copyroot = FALSE;
      svn_fs_root_t *copyroot_root;
      dag_node_t *copyroot_node;

      /* We're trying to clone somebody's child.  Make sure our parent
         is mutable.  */
      SVN_ERR(make_path_mutable(root, parent_path->parent,
                                error_path, pool));

      switch (inherit)
        {
        case copy_id_inherit_parent:
          parent_id = svn_fs_fs__dag_get_id(parent_path->parent->node);
          copy_id = *svn_fs_fs__id_copy_id(parent_id);
          break;

        case copy_id_inherit_new:
          SVN_ERR(svn_fs_fs__reserve_copy_id(&copy_id, root->fs, txn_id,
                                             pool));
          break;

        case copy_id_inherit_self:
          copy_id_ptr = NULL;
          break;

        case copy_id_inherit_unknown:
        default:
          SVN_ERR_MALFUNCTION(); /* uh-oh -- somebody didn't calculate copy-ID
                      inheritance data. */
        }

      /* Determine what copyroot our new child node should use. */
      SVN_ERR(svn_fs_fs__dag_get_copyroot(&copyroot_rev, &copyroot_path,
                                          parent_path->node));
      SVN_ERR(svn_fs_fs__revision_root(&copyroot_root, root->fs,
                                       copyroot_rev, pool));
      SVN_ERR(get_dag(&copyroot_node, copyroot_root, copyroot_path, pool));

      child_id = svn_fs_fs__dag_get_id(parent_path->node);
      copyroot_id = svn_fs_fs__dag_get_id(copyroot_node);
      if (!svn_fs_fs__id_part_eq(svn_fs_fs__id_node_id(child_id),
                                 svn_fs_fs__id_node_id(copyroot_id)))
        is_parent_copyroot = TRUE;

      /* Now make this node mutable.  */
      clone_path = parent_path_path(parent_path->parent, pool);
      SVN_ERR(svn_fs_fs__dag_clone_child(&clone,
                                         parent_path->parent->node,
                                         clone_path,
                                         parent_path->entry,
                                         copy_id_ptr, txn_id,
                                         is_parent_copyroot,
                                         pool));

      /* Update the path cache. */
      SVN_ERR(dag_node_cache_set(root, parent_path_path(parent_path, pool),
                                 clone, pool));
    }
  else
    {
      /* We're trying to clone the root directory.  */
      SVN_ERR(mutable_root_node(&clone, root, error_path, pool));
    }

  /* Update the PARENT_PATH link to refer to the clone.  */
  parent_path->node = clone;

  return SVN_NO_ERROR;
}