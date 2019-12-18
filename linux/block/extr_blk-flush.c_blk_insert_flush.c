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
struct request_queue {unsigned long queue_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  saved_end_io; int /*<<< orphan*/  list; } ;
struct request {scalar_t__ bio; scalar_t__ biotail; int /*<<< orphan*/  end_io; TYPE_1__ flush; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  mq_ctx; struct request_queue* q; } ;
struct blk_flush_queue {int /*<<< orphan*/  mq_flush_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long QUEUE_FLAG_FUA ; 
 unsigned int REQ_FSEQ_ACTIONS ; 
 unsigned int REQ_FSEQ_DATA ; 
 unsigned int REQ_FSEQ_POSTFLUSH ; 
 unsigned int REQ_FSEQ_PREFLUSH ; 
 int /*<<< orphan*/  REQ_FUA ; 
 int /*<<< orphan*/  REQ_PREFLUSH ; 
 int /*<<< orphan*/  REQ_SYNC ; 
 int /*<<< orphan*/  RQF_FLUSH_SEQ ; 
 int /*<<< orphan*/  blk_flush_complete_seq (struct request*,struct blk_flush_queue*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int blk_flush_policy (unsigned long,struct request*) ; 
 struct blk_flush_queue* blk_get_flush_queue (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_request_bypass_insert (struct request*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mq_flush_data_end_io ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void blk_insert_flush(struct request *rq)
{
	struct request_queue *q = rq->q;
	unsigned long fflags = q->queue_flags;	/* may change, cache */
	unsigned int policy = blk_flush_policy(fflags, rq);
	struct blk_flush_queue *fq = blk_get_flush_queue(q, rq->mq_ctx);

	/*
	 * @policy now records what operations need to be done.  Adjust
	 * REQ_PREFLUSH and FUA for the driver.
	 */
	rq->cmd_flags &= ~REQ_PREFLUSH;
	if (!(fflags & (1UL << QUEUE_FLAG_FUA)))
		rq->cmd_flags &= ~REQ_FUA;

	/*
	 * REQ_PREFLUSH|REQ_FUA implies REQ_SYNC, so if we clear any
	 * of those flags, we have to set REQ_SYNC to avoid skewing
	 * the request accounting.
	 */
	rq->cmd_flags |= REQ_SYNC;

	/*
	 * An empty flush handed down from a stacking driver may
	 * translate into nothing if the underlying device does not
	 * advertise a write-back cache.  In this case, simply
	 * complete the request.
	 */
	if (!policy) {
		blk_mq_end_request(rq, 0);
		return;
	}

	BUG_ON(rq->bio != rq->biotail); /*assumes zero or single bio rq */

	/*
	 * If there's data but flush is not necessary, the request can be
	 * processed directly without going through flush machinery.  Queue
	 * for normal execution.
	 */
	if ((policy & REQ_FSEQ_DATA) &&
	    !(policy & (REQ_FSEQ_PREFLUSH | REQ_FSEQ_POSTFLUSH))) {
		blk_mq_request_bypass_insert(rq, false);
		return;
	}

	/*
	 * @rq should go through flush machinery.  Mark it part of flush
	 * sequence and submit for further processing.
	 */
	memset(&rq->flush, 0, sizeof(rq->flush));
	INIT_LIST_HEAD(&rq->flush.list);
	rq->rq_flags |= RQF_FLUSH_SEQ;
	rq->flush.saved_end_io = rq->end_io; /* Usually NULL */

	rq->end_io = mq_flush_data_end_io;

	spin_lock_irq(&fq->mq_flush_lock);
	blk_flush_complete_seq(rq, fq, REQ_FSEQ_ACTIONS & ~policy, 0);
	spin_unlock_irq(&fq->mq_flush_lock);
}