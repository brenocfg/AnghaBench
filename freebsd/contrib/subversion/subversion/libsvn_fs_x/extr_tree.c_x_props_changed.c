#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_GENERAL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__dag_things_different (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_node (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_props_changed(svn_boolean_t *changed_p,
                svn_fs_root_t *root1,
                const char *path1,
                svn_fs_root_t *root2,
                const char *path2,
                svn_boolean_t strict,
                apr_pool_t *scratch_pool)
{
  dag_node_t *node1, *node2;
  apr_pool_t *subpool = svn_pool_create(scratch_pool);

  /* Check that roots are in the same fs. */
  if (root1->fs != root2->fs)
    return svn_error_create
      (SVN_ERR_FS_GENERAL, NULL,
       _("Cannot compare property value between two different filesystems"));

  SVN_ERR(svn_fs_x__get_dag_node(&node1, root1, path1, subpool, subpool));
  SVN_ERR(svn_fs_x__get_temp_dag_node(&node2, root2, path2, subpool));
  SVN_ERR(svn_fs_x__dag_things_different(changed_p, NULL, node1, node2,
                                         strict, subpool));
  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}