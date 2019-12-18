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
struct bfq_queue {int /*<<< orphan*/  new_ioprio_class; int /*<<< orphan*/  ioprio_class; int /*<<< orphan*/  new_ioprio; int /*<<< orphan*/  ioprio; } ;
struct bfq_group {int /*<<< orphan*/  sched_data; } ;
struct bfq_entity {int /*<<< orphan*/ * sched_data; int /*<<< orphan*/  new_weight; int /*<<< orphan*/  orig_weight; int /*<<< orphan*/  weight; } ;

/* Variables and functions */
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 

void bfq_init_entity(struct bfq_entity *entity, struct bfq_group *bfqg)
{
	struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->weight = entity->new_weight;
	entity->orig_weight = entity->new_weight;
	if (bfqq) {
		bfqq->ioprio = bfqq->new_ioprio;
		bfqq->ioprio_class = bfqq->new_ioprio_class;
	}
	entity->sched_data = &bfqg->sched_data;
}