#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_fs_x__dag_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__get_dag_node(dag_node_t **dag_node_p,
                       svn_fs_root_t *root,
                       const char *path,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  dag_node_t *node = NULL;
  SVN_ERR(svn_fs_x__get_temp_dag_node(&node, root, path, scratch_pool));

  /* We want the returned node to live in POOL. */
  *dag_node_p = svn_fs_x__dag_dup(node, result_pool);

  return SVN_NO_ERROR;
}