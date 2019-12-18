#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_proplist_args {int /*<<< orphan*/ ** table_p; int /*<<< orphan*/  path; int /*<<< orphan*/  root; } ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_node_proplist(void *baton, trail_t *trail)
{
  struct node_proplist_args *args = baton;
  dag_node_t *node;
  apr_hash_t *proplist;

  SVN_ERR(get_dag(&node, args->root, args->path, trail, trail->pool));
  SVN_ERR(svn_fs_base__dag_get_proplist(&proplist, node,
                                        trail, trail->pool));
  *args->table_p = proplist ? proplist : apr_hash_make(trail->pool);
  return SVN_NO_ERROR;
}