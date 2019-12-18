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
struct bfq_service_tree {int /*<<< orphan*/  vtime; int /*<<< orphan*/  idle; int /*<<< orphan*/  active; } ;
struct bfq_sched_data {struct bfq_entity* in_service_entity; } ;
struct bfq_entity {int /*<<< orphan*/  finish; int /*<<< orphan*/ * tree; scalar_t__ service; int /*<<< orphan*/  on_st; struct bfq_sched_data* sched_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_active_extract (struct bfq_service_tree*,struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_calc_finish (struct bfq_entity*,scalar_t__) ; 
 struct bfq_service_tree* bfq_entity_service_tree (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_forget_entity (struct bfq_service_tree*,struct bfq_entity*,int) ; 
 int /*<<< orphan*/  bfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_idle_extract (struct bfq_service_tree*,struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_idle_insert (struct bfq_service_tree*,struct bfq_entity*) ; 

bool __bfq_deactivate_entity(struct bfq_entity *entity, bool ins_into_idle_tree)
{
	struct bfq_sched_data *sd = entity->sched_data;
	struct bfq_service_tree *st;
	bool is_in_service;

	if (!entity->on_st) /* entity never activated, or already inactive */
		return false;

	/*
	 * If we get here, then entity is active, which implies that
	 * bfq_group_set_parent has already been invoked for the group
	 * represented by entity. Therefore, the field
	 * entity->sched_data has been set, and we can safely use it.
	 */
	st = bfq_entity_service_tree(entity);
	is_in_service = entity == sd->in_service_entity;

	bfq_calc_finish(entity, entity->service);

	if (is_in_service)
		sd->in_service_entity = NULL;
	else
		/*
		 * Non in-service entity: nobody will take care of
		 * resetting its service counter on expiration. Do it
		 * now.
		 */
		entity->service = 0;

	if (entity->tree == &st->active)
		bfq_active_extract(st, entity);
	else if (!is_in_service && entity->tree == &st->idle)
		bfq_idle_extract(st, entity);

	if (!ins_into_idle_tree || !bfq_gt(entity->finish, st->vtime))
		bfq_forget_entity(st, entity, is_in_service);
	else
		bfq_idle_insert(st, entity);

	return true;
}