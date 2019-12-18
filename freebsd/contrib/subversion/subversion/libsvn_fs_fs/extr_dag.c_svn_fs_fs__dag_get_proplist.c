#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_node_revision (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_fs__get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__dag_get_proplist(apr_hash_t **proplist_p,
                            dag_node_t *node,
                            apr_pool_t *pool)
{
  node_revision_t *noderev;
  apr_hash_t *proplist = NULL;

  SVN_ERR(get_node_revision(&noderev, node));

  SVN_ERR(svn_fs_fs__get_proplist(&proplist, node->fs,
                                  noderev, pool));

  *proplist_p = proplist;

  return SVN_NO_ERROR;
}