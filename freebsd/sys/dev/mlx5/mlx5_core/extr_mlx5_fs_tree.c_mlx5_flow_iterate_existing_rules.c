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
struct mlx5_flow_namespace {int /*<<< orphan*/  dests_rw_sem; int /*<<< orphan*/  notifiers_rw_sem; } ;
typedef  int /*<<< orphan*/  rule_event_fn ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_rules_in_ns (struct mlx5_flow_namespace*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void mlx5_flow_iterate_existing_rules(struct mlx5_flow_namespace *ns,
					 rule_event_fn add_rule_cb,
					 void *context)
{
	down_write(&ns->dests_rw_sem);
	down_read(&ns->notifiers_rw_sem);
	iterate_rules_in_ns(ns, add_rule_cb, context);
	up_read(&ns->notifiers_rw_sem);
	up_write(&ns->dests_rw_sem);
}