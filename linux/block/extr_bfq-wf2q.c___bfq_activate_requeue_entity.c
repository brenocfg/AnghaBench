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
struct bfq_service_tree {int /*<<< orphan*/  active; } ;
struct bfq_sched_data {struct bfq_entity* in_service_entity; } ;
struct bfq_entity {int /*<<< orphan*/ * tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bfq_activate_entity (struct bfq_entity*,int) ; 
 int /*<<< orphan*/  __bfq_requeue_entity (struct bfq_entity*) ; 
 struct bfq_service_tree* bfq_entity_service_tree (struct bfq_entity*) ; 

__attribute__((used)) static void __bfq_activate_requeue_entity(struct bfq_entity *entity,
					  struct bfq_sched_data *sd,
					  bool non_blocking_wait_rq)
{
	struct bfq_service_tree *st = bfq_entity_service_tree(entity);

	if (sd->in_service_entity == entity || entity->tree == &st->active)
		 /*
		  * in service or already queued on the active tree,
		  * requeue or reposition
		  */
		__bfq_requeue_entity(entity);
	else
		/*
		 * Not in service and not queued on its active tree:
		 * the activity is idle and this is a true activation.
		 */
		__bfq_activate_entity(entity, non_blocking_wait_rq);
}