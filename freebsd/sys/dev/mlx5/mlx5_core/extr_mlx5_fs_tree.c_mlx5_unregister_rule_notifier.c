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
struct mlx5_flow_handler {int /*<<< orphan*/  list; struct mlx5_flow_namespace* ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_rules_in_ns (struct mlx5_flow_namespace*,int /*<<< orphan*/ ,struct mlx5_flow_handler*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_handler*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_from_clients ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void mlx5_unregister_rule_notifier(struct mlx5_flow_handler *handler)
{
	struct mlx5_flow_namespace *ns = handler->ns;

	/*Remove from dst's clients*/
	down_write(&ns->dests_rw_sem);
	down_write(&ns->notifiers_rw_sem);
	iterate_rules_in_ns(ns, remove_from_clients, handler);
	list_del(&handler->list);
	up_write(&ns->notifiers_rw_sem);
	up_write(&ns->dests_rw_sem);
	kfree(handler);
}