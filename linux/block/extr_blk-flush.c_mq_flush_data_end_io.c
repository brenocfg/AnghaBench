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
struct request_queue {scalar_t__ elevator; } ;
struct request {scalar_t__ tag; struct blk_mq_ctx* mq_ctx; struct blk_mq_hw_ctx* mq_hctx; struct request_queue* q; } ;
struct blk_mq_hw_ctx {int dummy; } ;
struct blk_mq_ctx {int dummy; } ;
struct blk_flush_queue {int /*<<< orphan*/  mq_flush_lock; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_FSEQ_DATA ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  blk_flush_complete_seq (struct request*,struct blk_flush_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct blk_flush_queue* blk_get_flush_queue (struct request_queue*,struct blk_mq_ctx*) ; 
 int /*<<< orphan*/  blk_mq_put_driver_tag (struct request*) ; 
 int /*<<< orphan*/  blk_mq_sched_restart (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mq_flush_data_end_io(struct request *rq, blk_status_t error)
{
	struct request_queue *q = rq->q;
	struct blk_mq_hw_ctx *hctx = rq->mq_hctx;
	struct blk_mq_ctx *ctx = rq->mq_ctx;
	unsigned long flags;
	struct blk_flush_queue *fq = blk_get_flush_queue(q, ctx);

	if (q->elevator) {
		WARN_ON(rq->tag < 0);
		blk_mq_put_driver_tag(rq);
	}

	/*
	 * After populating an empty queue, kick it to avoid stall.  Read
	 * the comment in flush_end_io().
	 */
	spin_lock_irqsave(&fq->mq_flush_lock, flags);
	blk_flush_complete_seq(rq, fq, REQ_FSEQ_DATA, error);
	spin_unlock_irqrestore(&fq->mq_flush_lock, flags);

	blk_mq_sched_restart(hctx);
}