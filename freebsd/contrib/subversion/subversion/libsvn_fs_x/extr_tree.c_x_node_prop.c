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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_node_prop(svn_string_t **value_p,
            svn_fs_root_t *root,
            const char *path,
            const char *propname,
            apr_pool_t *pool)
{
  dag_node_t *node;
  apr_hash_t *proplist;
  apr_pool_t *scratch_pool = svn_pool_create(pool);

  SVN_ERR(svn_fs_x__get_temp_dag_node(&node, root, path, scratch_pool));
  SVN_ERR(svn_fs_x__dag_get_proplist(&proplist, node, scratch_pool,
                                     scratch_pool));
  *value_p = NULL;
  if (proplist)
    *value_p = svn_string_dup(svn_hash_gets(proplist, propname), pool);

  svn_pool_destroy(scratch_pool);
  return SVN_NO_ERROR;
}