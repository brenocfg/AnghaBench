#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_2__* SVN_NO_ERROR ; 
 TYPE_2__* get_dag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_revision_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__get_path_created_rev(svn_revnum_t *rev,
                                  const char *path,
                                  trail_t *trail,
                                  apr_pool_t *pool)
{
  svn_revnum_t head_rev, created_rev;
  svn_fs_root_t *root;
  dag_node_t *root_dir, *path_node;
  svn_error_t *err;

  /* Get HEAD revision, */
  SVN_ERR(svn_fs_bdb__youngest_rev(&head_rev, trail->fs, trail, pool));

  /* Then convert it into a root_t, */
  SVN_ERR(svn_fs_base__dag_revision_root(&root_dir, trail->fs, head_rev,
                                         trail, pool));
  root = make_revision_root(trail->fs, head_rev, root_dir, pool);

  /* And get the dag_node for path in the root_t. */
  err = get_dag(&path_node, root, path, trail, pool);
  if (err && (err->apr_err == SVN_ERR_FS_NOT_FOUND))
    {
      svn_error_clear(err);
      *rev = SVN_INVALID_REVNUM;
      return SVN_NO_ERROR;
    }
  else if (err)
    return svn_error_trace(err);

  /* Find the created_rev of the dag_node. */
  SVN_ERR(svn_fs_base__dag_get_revision(&created_rev, path_node,
                                        trail, pool));

  *rev = created_rev;
  return SVN_NO_ERROR;
}