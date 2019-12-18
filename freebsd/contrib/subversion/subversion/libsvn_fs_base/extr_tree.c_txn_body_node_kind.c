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
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_kind_args {int /*<<< orphan*/  kind; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  dag_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_node_kind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
txn_body_node_kind(void *baton, trail_t *trail)
{
  struct node_kind_args *args = baton;
  dag_node_t *node;

  SVN_ERR(svn_fs_base__dag_get_node(&node, trail->fs, args->id,
                                    trail, trail->pool));
  args->kind = svn_fs_base__dag_node_kind(node);

  return SVN_NO_ERROR;
}