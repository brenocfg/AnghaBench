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
struct bfq_queue {int /*<<< orphan*/  bfqd; } ;
struct bfq_entity {int /*<<< orphan*/  weight; scalar_t__ finish; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ bfq_delta (unsigned long,int /*<<< orphan*/ ) ; 
 struct bfq_queue* bfq_entity_to_bfqq (struct bfq_entity*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (int /*<<< orphan*/ ,struct bfq_queue*,char*,unsigned long,scalar_t__,...) ; 

__attribute__((used)) static void bfq_calc_finish(struct bfq_entity *entity, unsigned long service)
{
	struct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->finish = entity->start +
		bfq_delta(service, entity->weight);

	if (bfqq) {
		bfq_log_bfqq(bfqq->bfqd, bfqq,
			"calc_finish: serv %lu, w %d",
			service, entity->weight);
		bfq_log_bfqq(bfqq->bfqd, bfqq,
			"calc_finish: start %llu, finish %llu, delta %llu",
			entity->start, entity->finish,
			bfq_delta(service, entity->weight));
	}
}