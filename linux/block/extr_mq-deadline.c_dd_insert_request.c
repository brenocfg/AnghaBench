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
struct request {int /*<<< orphan*/  queuelist; scalar_t__ fifo_time; } ;
struct deadline_data {int /*<<< orphan*/ * fifo_list; scalar_t__* fifo_expire; int /*<<< orphan*/  dispatch; } ;
struct blk_mq_hw_ctx {struct request_queue* queue; } ;
struct TYPE_2__ {struct deadline_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_sched_request_inserted (struct request*) ; 
 scalar_t__ blk_mq_sched_try_insert_merge (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_req_zone_write_unlock (struct request*) ; 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  deadline_add_rq_rb (struct deadline_data*,struct request*) ; 
 int /*<<< orphan*/  elv_rqhash_add (struct request_queue*,struct request*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rq_data_dir (struct request*) ; 
 scalar_t__ rq_mergeable (struct request*) ; 

__attribute__((used)) static void dd_insert_request(struct blk_mq_hw_ctx *hctx, struct request *rq,
			      bool at_head)
{
	struct request_queue *q = hctx->queue;
	struct deadline_data *dd = q->elevator->elevator_data;
	const int data_dir = rq_data_dir(rq);

	/*
	 * This may be a requeue of a write request that has locked its
	 * target zone. If it is the case, this releases the zone lock.
	 */
	blk_req_zone_write_unlock(rq);

	if (blk_mq_sched_try_insert_merge(q, rq))
		return;

	blk_mq_sched_request_inserted(rq);

	if (at_head || blk_rq_is_passthrough(rq)) {
		if (at_head)
			list_add(&rq->queuelist, &dd->dispatch);
		else
			list_add_tail(&rq->queuelist, &dd->dispatch);
	} else {
		deadline_add_rq_rb(dd, rq);

		if (rq_mergeable(rq)) {
			elv_rqhash_add(q, rq);
			if (!q->last_merge)
				q->last_merge = rq;
		}

		/*
		 * set expire time and add to fifo list
		 */
		rq->fifo_time = jiffies + dd->fifo_expire[data_dir];
		list_add_tail(&rq->queuelist, &dd->fifo_list[data_dir]);
	}
}