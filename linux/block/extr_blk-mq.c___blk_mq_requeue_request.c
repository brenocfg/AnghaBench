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
struct request_queue {scalar_t__ dma_drain_size; } ;
struct request {int /*<<< orphan*/  nr_phys_segments; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  state; struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  MQ_RQ_IDLE ; 
 int /*<<< orphan*/  RQF_TIMED_OUT ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_put_driver_tag (struct request*) ; 
 scalar_t__ blk_mq_request_started (struct request*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  rq_qos_requeue (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  trace_block_rq_requeue (struct request_queue*,struct request*) ; 

__attribute__((used)) static void __blk_mq_requeue_request(struct request *rq)
{
	struct request_queue *q = rq->q;

	blk_mq_put_driver_tag(rq);

	trace_block_rq_requeue(q, rq);
	rq_qos_requeue(q, rq);

	if (blk_mq_request_started(rq)) {
		WRITE_ONCE(rq->state, MQ_RQ_IDLE);
		rq->rq_flags &= ~RQF_TIMED_OUT;
		if (q->dma_drain_size && blk_rq_bytes(rq))
			rq->nr_phys_segments--;
	}
}