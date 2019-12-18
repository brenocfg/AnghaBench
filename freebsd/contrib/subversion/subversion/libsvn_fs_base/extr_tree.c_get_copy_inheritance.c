#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  node; TYPE_1__* parent; } ;
typedef  TYPE_2__ parent_path_t ;
struct TYPE_9__ {int /*<<< orphan*/  dst_noderev_id; } ;
typedef  TYPE_3__ copy_t ;
typedef  int /*<<< orphan*/  copy_id_inherit_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  copy_id_inherit_new ; 
 int /*<<< orphan*/  copy_id_inherit_parent ; 
 int /*<<< orphan*/  copy_id_inherit_self ; 
 char const* parent_path_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* svn_fs_base__dag_get_created_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_id (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_base__id_compare (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 char* svn_fs_base__id_copy_id (int /*<<< orphan*/  const*) ; 
 char const* svn_fs_base__id_txn_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_copy (TYPE_3__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_node_unrelated ; 

__attribute__((used)) static svn_error_t *
get_copy_inheritance(copy_id_inherit_t *inherit_p,
                     const char **copy_src_path,
                     svn_fs_t *fs,
                     parent_path_t *child,
                     const char *txn_id,
                     trail_t *trail,
                     apr_pool_t *pool)
{
  const svn_fs_id_t *child_id, *parent_id;
  const char *child_copy_id, *parent_copy_id;
  const char *id_path = NULL;

  SVN_ERR_ASSERT(child && child->parent && txn_id);

  /* Initialize our return variables (default: self-inheritance). */
  *inherit_p = copy_id_inherit_self;
  *copy_src_path = NULL;

  /* Initialize some convenience variables. */
  child_id = svn_fs_base__dag_get_id(child->node);
  parent_id = svn_fs_base__dag_get_id(child->parent->node);
  child_copy_id = svn_fs_base__id_copy_id(child_id);
  parent_copy_id = svn_fs_base__id_copy_id(parent_id);

  /* Easy out: if this child is already mutable, we have nothing to do. */
  if (strcmp(svn_fs_base__id_txn_id(child_id), txn_id) == 0)
    return SVN_NO_ERROR;

  /* If the child and its parent are on the same branch, then the
     child will inherit the copy ID of its parent when made mutable.
     This is trivially detectable when the child and its parent have
     the same copy ID.  But that's not the sole indicator of
     same-branchness.  It might be the case that the parent was the
     result of a copy, but the child has not yet been cloned for
     mutability since that copy.  Detection of this latter case
     basically means making sure the copy IDs don't differ for some
     other reason, such as that the child was the direct target of the
     copy whose ID it has.  There is a special case here, too -- if
     the child's copy ID is the special ID "0", it can't have been the
     target of any copy, and therefore must be on the same branch as
     its parent.  */
  if ((strcmp(child_copy_id, "0") == 0)
      || (strcmp(child_copy_id, parent_copy_id) == 0))
    {
      *inherit_p = copy_id_inherit_parent;
      return SVN_NO_ERROR;
    }
  else
    {
      copy_t *copy;
      SVN_ERR(svn_fs_bdb__get_copy(&copy, fs, child_copy_id, trail, pool));
      if (   svn_fs_base__id_compare(copy->dst_noderev_id, child_id)
          == svn_fs_node_unrelated)
        {
          *inherit_p = copy_id_inherit_parent;
          return SVN_NO_ERROR;
        }
    }

  /* If we get here, the child and its parent are not on speaking
     terms -- there will be no parental inheritance handed down in
     *this* generation. */

  /* If the child was created at a different path than the one we are
     expecting its clone to live, one of its parents must have been
     created via a copy since the child was created.  The child isn't
     on the same branch as its parent (we caught those cases early);
     it can't keep its current copy ID because there's been an
     affecting copy (its clone won't be on the same branch as the
     child is).  That leaves only one course of action -- to assign
     the child a brand new "soft" copy ID. */
  id_path = svn_fs_base__dag_get_created_path(child->node);
  if (strcmp(id_path, parent_path_path(child, pool)) != 0)
    {
      *inherit_p = copy_id_inherit_new;
      *copy_src_path = id_path;
      return SVN_NO_ERROR;
    }

  /* The node gets to keep its own ID. */
  return SVN_NO_ERROR;
}