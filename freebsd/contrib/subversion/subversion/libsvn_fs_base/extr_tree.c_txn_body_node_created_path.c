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
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_created_path_args {int /*<<< orphan*/ * created_path; int /*<<< orphan*/  path; int /*<<< orphan*/  root; } ;
typedef  int /*<<< orphan*/  dag_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_created_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
txn_body_node_created_path(void *baton, trail_t *trail)
{
  struct node_created_path_args *args = baton;
  dag_node_t *node;

  SVN_ERR(get_dag(&node, args->root, args->path, trail, trail->pool));
  *args->created_path = svn_fs_base__dag_get_created_path(node);
  return SVN_NO_ERROR;
}