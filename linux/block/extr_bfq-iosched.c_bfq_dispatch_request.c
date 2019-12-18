#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct blk_mq_hw_ctx {TYPE_2__* queue; } ;
struct bfq_queue {int dummy; } ;
struct bfq_data {int /*<<< orphan*/  lock; struct bfq_queue* in_service_queue; } ;
struct TYPE_4__ {TYPE_1__* elevator; } ;
struct TYPE_3__ {struct bfq_data* elevator_data; } ;

/* Variables and functions */
 struct request* __bfq_dispatch_request (struct blk_mq_hw_ctx*) ; 
 scalar_t__ bfq_bfqq_wait_request (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_update_dispatch_stats (TYPE_2__*,struct request*,struct bfq_queue*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct request *bfq_dispatch_request(struct blk_mq_hw_ctx *hctx)
{
	struct bfq_data *bfqd = hctx->queue->elevator->elevator_data;
	struct request *rq;
	struct bfq_queue *in_serv_queue;
	bool waiting_rq, idle_timer_disabled;

	spin_lock_irq(&bfqd->lock);

	in_serv_queue = bfqd->in_service_queue;
	waiting_rq = in_serv_queue && bfq_bfqq_wait_request(in_serv_queue);

	rq = __bfq_dispatch_request(hctx);

	idle_timer_disabled =
		waiting_rq && !bfq_bfqq_wait_request(in_serv_queue);

	spin_unlock_irq(&bfqd->lock);

	bfq_update_dispatch_stats(hctx->queue, rq, in_serv_queue,
				  idle_timer_disabled);

	return rq;
}