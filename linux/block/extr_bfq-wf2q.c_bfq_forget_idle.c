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
struct bfq_service_tree {int /*<<< orphan*/  vtime; int /*<<< orphan*/  active; struct bfq_entity* last_idle; struct bfq_entity* first_idle; } ;
struct bfq_entity {int /*<<< orphan*/  finish; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_put_idle_entity (struct bfq_service_tree*,struct bfq_entity*) ; 

__attribute__((used)) static void bfq_forget_idle(struct bfq_service_tree *st)
{
	struct bfq_entity *first_idle = st->first_idle;
	struct bfq_entity *last_idle = st->last_idle;

	if (RB_EMPTY_ROOT(&st->active) && last_idle &&
	    !bfq_gt(last_idle->finish, st->vtime)) {
		/*
		 * Forget the whole idle tree, increasing the vtime past
		 * the last finish time of idle entities.
		 */
		st->vtime = last_idle->finish;
	}

	if (first_idle && !bfq_gt(first_idle->finish, st->vtime))
		bfq_put_idle_entity(st, first_idle);
}