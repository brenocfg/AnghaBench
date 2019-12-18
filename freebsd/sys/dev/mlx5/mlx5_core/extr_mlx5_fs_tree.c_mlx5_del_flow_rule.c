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
struct mlx5_flow_rule {int /*<<< orphan*/  base; } ;
struct mlx5_flow_namespace {int /*<<< orphan*/  dests_rw_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_remove_node (int /*<<< orphan*/ *) ; 
 struct mlx5_flow_namespace* get_ns_with_notifiers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void mlx5_del_flow_rule(struct mlx5_flow_rule *dst)
{
	struct mlx5_flow_namespace *ns;

	ns = get_ns_with_notifiers(&dst->base);
	if (ns)
		down_read(&ns->dests_rw_sem);
	fs_remove_node(&dst->base);
	if (ns)
		up_read(&ns->dests_rw_sem);
}