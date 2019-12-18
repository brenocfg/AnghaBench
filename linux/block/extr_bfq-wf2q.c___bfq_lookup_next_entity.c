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
typedef  int /*<<< orphan*/  u64 ;
struct bfq_service_tree {int /*<<< orphan*/  active; } ;
struct bfq_entity {int dummy; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfq_calc_vtime_jump (struct bfq_service_tree*) ; 
 struct bfq_entity* bfq_first_active_entity (struct bfq_service_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_update_vtime (struct bfq_service_tree*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bfq_entity *
__bfq_lookup_next_entity(struct bfq_service_tree *st, bool in_service)
{
	struct bfq_entity *entity;
	u64 new_vtime;

	if (RB_EMPTY_ROOT(&st->active))
		return NULL;

	/*
	 * Get the value of the system virtual time for which at
	 * least one entity is eligible.
	 */
	new_vtime = bfq_calc_vtime_jump(st);

	/*
	 * If there is no in-service entity for the sched_data this
	 * active tree belongs to, then push the system virtual time
	 * up to the value that guarantees that at least one entity is
	 * eligible. If, instead, there is an in-service entity, then
	 * do not make any such update, because there is already an
	 * eligible entity, namely the in-service one (even if the
	 * entity is not on st, because it was extracted when set in
	 * service).
	 */
	if (!in_service)
		bfq_update_vtime(st, new_vtime);

	entity = bfq_first_active_entity(st, new_vtime);

	return entity;
}