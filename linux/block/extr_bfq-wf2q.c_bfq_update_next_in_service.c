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
struct bfq_service_tree {int /*<<< orphan*/  vtime; } ;
struct bfq_sched_data {struct bfq_entity* next_in_service; struct bfq_service_tree* service_tree; } ;
struct bfq_entity {int /*<<< orphan*/  finish; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 unsigned int bfq_class_idx (struct bfq_entity*) ; 
 scalar_t__ bfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bfq_entity* bfq_lookup_next_entity (struct bfq_sched_data*,int) ; 
 int bfq_update_parent_budget (struct bfq_entity*) ; 

__attribute__((used)) static bool bfq_update_next_in_service(struct bfq_sched_data *sd,
				       struct bfq_entity *new_entity,
				       bool expiration)
{
	struct bfq_entity *next_in_service = sd->next_in_service;
	bool parent_sched_may_change = false;
	bool change_without_lookup = false;

	/*
	 * If this update is triggered by the activation, requeueing
	 * or repositioning of an entity that does not coincide with
	 * sd->next_in_service, then a full lookup in the active tree
	 * can be avoided. In fact, it is enough to check whether the
	 * just-modified entity has the same priority as
	 * sd->next_in_service, is eligible and has a lower virtual
	 * finish time than sd->next_in_service. If this compound
	 * condition holds, then the new entity becomes the new
	 * next_in_service. Otherwise no change is needed.
	 */
	if (new_entity && new_entity != sd->next_in_service) {
		/*
		 * Flag used to decide whether to replace
		 * sd->next_in_service with new_entity. Tentatively
		 * set to true, and left as true if
		 * sd->next_in_service is NULL.
		 */
		change_without_lookup = true;

		/*
		 * If there is already a next_in_service candidate
		 * entity, then compare timestamps to decide whether
		 * to replace sd->service_tree with new_entity.
		 */
		if (next_in_service) {
			unsigned int new_entity_class_idx =
				bfq_class_idx(new_entity);
			struct bfq_service_tree *st =
				sd->service_tree + new_entity_class_idx;

			change_without_lookup =
				(new_entity_class_idx ==
				 bfq_class_idx(next_in_service)
				 &&
				 !bfq_gt(new_entity->start, st->vtime)
				 &&
				 bfq_gt(next_in_service->finish,
					new_entity->finish));
		}

		if (change_without_lookup)
			next_in_service = new_entity;
	}

	if (!change_without_lookup) /* lookup needed */
		next_in_service = bfq_lookup_next_entity(sd, expiration);

	if (next_in_service) {
		bool new_budget_triggers_change =
			bfq_update_parent_budget(next_in_service);

		parent_sched_may_change = !sd->next_in_service ||
			new_budget_triggers_change;
	}

	sd->next_in_service = next_in_service;

	if (!next_in_service)
		return parent_sched_may_change;

	return parent_sched_may_change;
}