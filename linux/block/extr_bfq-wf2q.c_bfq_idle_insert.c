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
struct bfq_service_tree {int /*<<< orphan*/  idle; struct bfq_entity* last_idle; struct bfq_entity* first_idle; } ;
struct bfq_queue {TYPE_1__* bfqd; int /*<<< orphan*/  bfqq_list; } ;
struct bfq_entity {int /*<<< orphan*/  finish; } ;
struct TYPE_2__ {int /*<<< orphan*/  idle_list; } ;

/* Variables and functions */
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 
 scalar_t__ bfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_insert (int /*<<< orphan*/ *,struct bfq_entity*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfq_idle_insert(struct bfq_service_tree *st,
			    struct bfq_entity *entity)
{
	struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	struct bfq_entity *first_idle = st->first_idle;
	struct bfq_entity *last_idle = st->last_idle;

	if (!first_idle || bfq_gt(first_idle->finish, entity->finish))
		st->first_idle = entity;
	if (!last_idle || bfq_gt(entity->finish, last_idle->finish))
		st->last_idle = entity;

	bfq_insert(&st->idle, entity);

	if (bfqq)
		list_add(&bfqq->bfqq_list, &bfqq->bfqd->idle_list);
}