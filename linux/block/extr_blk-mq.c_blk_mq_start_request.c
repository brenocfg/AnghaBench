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
struct TYPE_4__ {TYPE_1__* profile; } ;
struct request_queue {TYPE_2__ integrity; scalar_t__ dma_drain_size; int /*<<< orphan*/  queue_flags; } ;
struct request {int /*<<< orphan*/  nr_phys_segments; int /*<<< orphan*/  state; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  stats_sectors; int /*<<< orphan*/  io_start_time_ns; struct request_queue* q; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* prepare_fn ) (struct request*) ;} ;

/* Variables and functions */
 scalar_t__ MQ_RQ_IDLE ; 
 int /*<<< orphan*/  MQ_RQ_IN_FLIGHT ; 
 int /*<<< orphan*/  QUEUE_FLAG_STATS ; 
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  RQF_STATS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_add_timer (struct request*) ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 scalar_t__ blk_mq_rq_state (struct request*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 scalar_t__ req_op (struct request*) ; 
 int /*<<< orphan*/  rq_qos_issue (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_rq_issue (struct request_queue*,struct request*) ; 

void blk_mq_start_request(struct request *rq)
{
	struct request_queue *q = rq->q;

	trace_block_rq_issue(q, rq);

	if (test_bit(QUEUE_FLAG_STATS, &q->queue_flags)) {
		rq->io_start_time_ns = ktime_get_ns();
		rq->stats_sectors = blk_rq_sectors(rq);
		rq->rq_flags |= RQF_STATS;
		rq_qos_issue(q, rq);
	}

	WARN_ON_ONCE(blk_mq_rq_state(rq) != MQ_RQ_IDLE);

	blk_add_timer(rq);
	WRITE_ONCE(rq->state, MQ_RQ_IN_FLIGHT);

	if (q->dma_drain_size && blk_rq_bytes(rq)) {
		/*
		 * Make sure space for the drain appears.  We know we can do
		 * this because max_hw_segments has been adjusted to be one
		 * fewer than the device can handle.
		 */
		rq->nr_phys_segments++;
	}

#ifdef CONFIG_BLK_DEV_INTEGRITY
	if (blk_integrity_rq(rq) && req_op(rq) == REQ_OP_WRITE)
		q->integrity.profile->prepare_fn(rq);
#endif
}