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
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_x__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dir_entry_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__id_used (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__dag_open(dag_node_t **child_p,
                   dag_node_t *parent,
                   const char *name,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  svn_fs_x__id_t node_id;

  /* Ensure that NAME exists in PARENT's entry list. */
  SVN_ERR(svn_fs_x__dir_entry_id(&node_id, parent, name, scratch_pool));
  if (! svn_fs_x__id_used(&node_id))
    {
      *child_p = NULL;
      return SVN_NO_ERROR;
    }

  /* Now get the node that was requested. */
  return svn_fs_x__dag_get_node(child_p, svn_fs_x__dag_get_fs(parent),
                                &node_id, result_pool, scratch_pool);
}