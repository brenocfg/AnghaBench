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
struct request_queue {TYPE_1__* elevator; } ;
struct request {int /*<<< orphan*/  mq_hctx; struct request_queue* q; } ;
struct deadline_data {int /*<<< orphan*/  zone_lock; int /*<<< orphan*/ * fifo_list; } ;
struct TYPE_2__ {struct deadline_data* elevator_data; } ;

/* Variables and functions */
 size_t WRITE ; 
 int /*<<< orphan*/  blk_mq_sched_mark_restart_hctx (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_is_zoned (struct request_queue*) ; 
 int /*<<< orphan*/  blk_req_zone_write_unlock (struct request*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dd_finish_request(struct request *rq)
{
	struct request_queue *q = rq->q;

	if (blk_queue_is_zoned(q)) {
		struct deadline_data *dd = q->elevator->elevator_data;
		unsigned long flags;

		spin_lock_irqsave(&dd->zone_lock, flags);
		blk_req_zone_write_unlock(rq);
		if (!list_empty(&dd->fifo_list[WRITE]))
			blk_mq_sched_mark_restart_hctx(rq->mq_hctx);
		spin_unlock_irqrestore(&dd->zone_lock, flags);
	}
}