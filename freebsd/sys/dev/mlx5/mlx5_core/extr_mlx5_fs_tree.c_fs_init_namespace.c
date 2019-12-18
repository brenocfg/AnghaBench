#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct mlx5_flow_namespace {int /*<<< orphan*/  list_notifiers; int /*<<< orphan*/  prios; int /*<<< orphan*/  notifiers_rw_sem; int /*<<< orphan*/  dests_rw_sem; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_TYPE_NAMESPACE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_namespace *fs_init_namespace(struct mlx5_flow_namespace
						 *ns)
{
	ns->base.type = FS_TYPE_NAMESPACE;
	init_rwsem(&ns->dests_rw_sem);
	init_rwsem(&ns->notifiers_rw_sem);
	INIT_LIST_HEAD(&ns->prios);
	INIT_LIST_HEAD(&ns->list_notifiers);

	return ns;
}