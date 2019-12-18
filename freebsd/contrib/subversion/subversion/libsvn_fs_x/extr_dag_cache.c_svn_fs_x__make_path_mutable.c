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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_14__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;
struct TYPE_15__ {int copy_inherit; int /*<<< orphan*/ * node; int /*<<< orphan*/  entry; struct TYPE_15__* parent; } ;
typedef  TYPE_2__ svn_fs_x__dag_path_t ;
typedef  int svn_fs_x__copy_id_inherit_t ;
struct TYPE_16__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_3__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * mutable_root_node (int /*<<< orphan*/ **,TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* parent_path_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
#define  svn_fs_x__copy_id_inherit_new 131 
#define  svn_fs_x__copy_id_inherit_parent 130 
#define  svn_fs_x__copy_id_inherit_self 129 
#define  svn_fs_x__copy_id_inherit_unknown 128 
 scalar_t__ svn_fs_x__dag_check_mutable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__dag_clone_child (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_fs_x__dag_get_copy_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_copyroot (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_related_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,TYPE_3__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__reserve_copy_id (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__revision_root (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__root_txn_id (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_fs_x__update_dag_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__make_path_mutable(svn_fs_root_t *root,
                            svn_fs_x__dag_path_t *parent_path,
                            const char *error_path,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  dag_node_t *clone;
  svn_fs_x__txn_id_t txn_id = svn_fs_x__root_txn_id(root);

  /* Is the node mutable already?  */
  if (svn_fs_x__dag_check_mutable(parent_path->node))
    return SVN_NO_ERROR;

  /* Are we trying to clone the root, or somebody's child node?  */
  if (parent_path->parent)
    {
      svn_fs_x__id_t copy_id = { SVN_INVALID_REVNUM, 0 };
      svn_fs_x__id_t *copy_id_ptr = &copy_id;
      svn_fs_x__copy_id_inherit_t inherit = parent_path->copy_inherit;
      const char *clone_path, *copyroot_path;
      svn_revnum_t copyroot_rev;
      svn_boolean_t is_parent_copyroot = FALSE;
      svn_fs_root_t *copyroot_root;
      dag_node_t *copyroot_node;
      apr_pool_t *subpool;

      /* We're trying to clone somebody's child.  Make sure our parent
         is mutable.  */
      SVN_ERR(svn_fs_x__make_path_mutable(root, parent_path->parent,
                                          error_path, result_pool,
                                          scratch_pool));

      /* Allocate all temporaries in a sub-pool that we control locally.
         That way, we keep only the data of one level of recursion around
         at any time. */
      subpool = svn_pool_create(scratch_pool);
      switch (inherit)
        {
        case svn_fs_x__copy_id_inherit_parent:
          copy_id = *svn_fs_x__dag_get_copy_id(parent_path->parent->node);
          break;

        case svn_fs_x__copy_id_inherit_new:
          SVN_ERR(svn_fs_x__reserve_copy_id(&copy_id, root->fs, txn_id,
                                            subpool));
          break;

        case svn_fs_x__copy_id_inherit_self:
          copy_id_ptr = NULL;
          break;

        case svn_fs_x__copy_id_inherit_unknown:
        default:
          SVN_ERR_MALFUNCTION(); /* uh-oh -- somebody didn't calculate copy-ID
                      inheritance data. */
        }

      /* Determine what copyroot our new child node should use. */
      svn_fs_x__dag_get_copyroot(&copyroot_rev, &copyroot_path,
                                 parent_path->node);
      SVN_ERR(svn_fs_x__revision_root(&copyroot_root, root->fs,
                                      copyroot_rev, subpool));
      SVN_ERR(svn_fs_x__get_temp_dag_node(&copyroot_node, copyroot_root,
                                          copyroot_path, subpool));

      if (!svn_fs_x__dag_related_node(copyroot_node, parent_path->node))
        is_parent_copyroot = TRUE;

      /* Now make this node mutable.  */
      clone_path = parent_path_path(parent_path->parent, subpool);
      SVN_ERR(svn_fs_x__dag_clone_child(&clone,
                                        parent_path->parent->node,
                                        clone_path,
                                        parent_path->entry,
                                        copy_id_ptr, txn_id,
                                        is_parent_copyroot,
                                        result_pool,
                                        subpool));

      /* Update the path cache. */
      svn_fs_x__update_dag_cache(clone);
      svn_pool_destroy(subpool);
    }
  else
    {
      /* We're trying to clone the root directory.  */
      SVN_ERR(mutable_root_node(&clone, root, error_path, result_pool,
                                scratch_pool));
    }

  /* Update the PARENT_PATH link to refer to the clone.  */
  parent_path->node = clone;

  return SVN_NO_ERROR;
}