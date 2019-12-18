#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
struct TYPE_6__ {int /*<<< orphan*/  node; TYPE_1__* parent; } ;
typedef  TYPE_2__ svn_fs_x__dag_path_t ;
typedef  int /*<<< orphan*/  svn_fs_x__copy_id_inherit_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  parent_path_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__copy_id_inherit_new ; 
 int /*<<< orphan*/  svn_fs_x__copy_id_inherit_parent ; 
 int /*<<< orphan*/  svn_fs_x__copy_id_inherit_self ; 
 scalar_t__ svn_fs_x__dag_check_mutable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_x__dag_get_copy_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_copyroot (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 char* svn_fs_x__dag_get_created_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__dag_related_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__id_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__id_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_copy_inheritance(svn_fs_x__copy_id_inherit_t *inherit_p,
                     const char **copy_src_path,
                     svn_fs_t *fs,
                     svn_fs_x__dag_path_t *child,
                     apr_pool_t *scratch_pool)
{
  svn_fs_x__id_t child_copy_id, parent_copy_id;
  const char *id_path = NULL;
  svn_fs_root_t *copyroot_root;
  dag_node_t *copyroot_node;
  svn_revnum_t copyroot_rev;
  const char *copyroot_path;

  SVN_ERR_ASSERT(child && child->parent);

  /* Initialize some convenience variables. */
  child_copy_id = *svn_fs_x__dag_get_copy_id(child->node);
  parent_copy_id = *svn_fs_x__dag_get_copy_id(child->parent->node);

  /* By default, there is no copy source. */
  *copy_src_path = NULL;

  /* If this child is already mutable, we have nothing to do. */
  if (svn_fs_x__dag_check_mutable(child->node))
    {
      *inherit_p = svn_fs_x__copy_id_inherit_self;
      return SVN_NO_ERROR;
    }

  /* From this point on, we'll assume that the child will just take
     its copy ID from its parent. */
  *inherit_p = svn_fs_x__copy_id_inherit_parent;

  /* Special case: if the child's copy ID is '0', use the parent's
     copy ID. */
  if (svn_fs_x__id_is_root(&child_copy_id))
    return SVN_NO_ERROR;

  /* Compare the copy IDs of the child and its parent.  If they are
     the same, then the child is already on the same branch as the
     parent, and should use the same mutability copy ID that the
     parent will use. */
  if (svn_fs_x__id_eq(&child_copy_id, &parent_copy_id))
    return SVN_NO_ERROR;

  /* If the child is on the same branch that the parent is on, the
     child should just use the same copy ID that the parent would use.
     Else, the child needs to generate a new copy ID to use should it
     need to be made mutable.  We will claim that child is on the same
     branch as its parent if the child itself is not a branch point,
     or if it is a branch point that we are accessing via its original
     copy destination path. */
  svn_fs_x__dag_get_copyroot(&copyroot_rev, &copyroot_path, child->node);
  SVN_ERR(svn_fs_x__revision_root(&copyroot_root, fs, copyroot_rev, 
                                  scratch_pool));
  SVN_ERR(svn_fs_x__get_temp_dag_node(&copyroot_node, copyroot_root,
                                      copyroot_path, scratch_pool));

  if (!svn_fs_x__dag_related_node(copyroot_node, child->node))
    return SVN_NO_ERROR;

  /* Determine if we are looking at the child via its original path or
     as a subtree item of a copied tree. */
  id_path = svn_fs_x__dag_get_created_path(child->node);
  if (strcmp(id_path, parent_path_path(child, scratch_pool)) == 0)
    {
      *inherit_p = svn_fs_x__copy_id_inherit_self;
      return SVN_NO_ERROR;
    }

  /* We are pretty sure that the child node is an unedited nested
     branched node.  When it needs to be made mutable, it should claim
     a new copy ID. */
  *inherit_p = svn_fs_x__copy_id_inherit_new;
  *copy_src_path = id_path;
  return SVN_NO_ERROR;
}