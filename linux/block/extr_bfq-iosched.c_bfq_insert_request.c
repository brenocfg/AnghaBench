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
struct request_queue {struct request* last_merge; TYPE_1__* elevator; } ;
struct request {unsigned int cmd_flags; int /*<<< orphan*/  queuelist; } ;
struct blk_mq_hw_ctx {struct request_queue* queue; } ;
struct bfq_queue {int dummy; } ;
struct bfq_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dispatch; } ;
struct TYPE_2__ {struct bfq_data* elevator_data; } ;

/* Variables and functions */
 struct bfq_queue* RQ_BFQQ (struct request*) ; 
 int __bfq_insert_request (struct bfq_data*,struct request*) ; 
 struct bfq_queue* bfq_init_rq (struct request*) ; 
 int /*<<< orphan*/  bfq_update_insert_stats (struct request_queue*,struct bfq_queue*,int,unsigned int) ; 
 int /*<<< orphan*/  blk_mq_sched_request_inserted (struct request*) ; 
 scalar_t__ blk_mq_sched_try_insert_merge (struct request_queue*,struct request*) ; 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  elv_rqhash_add (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rq_mergeable (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfq_insert_request(struct blk_mq_hw_ctx *hctx, struct request *rq,
			       bool at_head)
{
	struct request_queue *q = hctx->queue;
	struct bfq_data *bfqd = q->elevator->elevator_data;
	struct bfq_queue *bfqq;
	bool idle_timer_disabled = false;
	unsigned int cmd_flags;

	spin_lock_irq(&bfqd->lock);
	if (blk_mq_sched_try_insert_merge(q, rq)) {
		spin_unlock_irq(&bfqd->lock);
		return;
	}

	spin_unlock_irq(&bfqd->lock);

	blk_mq_sched_request_inserted(rq);

	spin_lock_irq(&bfqd->lock);
	bfqq = bfq_init_rq(rq);
	if (!bfqq || at_head || blk_rq_is_passthrough(rq)) {
		if (at_head)
			list_add(&rq->queuelist, &bfqd->dispatch);
		else
			list_add_tail(&rq->queuelist, &bfqd->dispatch);
	} else {
		idle_timer_disabled = __bfq_insert_request(bfqd, rq);
		/*
		 * Update bfqq, because, if a queue merge has occurred
		 * in __bfq_insert_request, then rq has been
		 * redirected into a new queue.
		 */
		bfqq = RQ_BFQQ(rq);

		if (rq_mergeable(rq)) {
			elv_rqhash_add(q, rq);
			if (!q->last_merge)
				q->last_merge = rq;
		}
	}

	/*
	 * Cache cmd_flags before releasing scheduler lock, because rq
	 * may disappear afterwards (for example, because of a request
	 * merge).
	 */
	cmd_flags = rq->cmd_flags;

	spin_unlock_irq(&bfqd->lock);

	bfq_update_insert_stats(q, bfqq, idle_timer_disabled,
				cmd_flags);
}