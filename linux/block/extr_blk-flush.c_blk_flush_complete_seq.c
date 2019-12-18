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
struct request_queue {int dummy; } ;
struct TYPE_2__ {unsigned int seq; int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;
struct request {unsigned int cmd_flags; TYPE_1__ flush; struct list_head queuelist; struct request_queue* q; } ;
struct blk_flush_queue {size_t flush_pending_idx; struct list_head flush_data_in_flight; int /*<<< orphan*/  flush_pending_since; struct list_head* flush_queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  REQ_FSEQ_DATA 131 
#define  REQ_FSEQ_DONE 130 
#define  REQ_FSEQ_POSTFLUSH 129 
#define  REQ_FSEQ_PREFLUSH 128 
 unsigned int blk_flush_cur_seq (struct request*) ; 
 int /*<<< orphan*/  blk_flush_queue_rq (struct request*,int) ; 
 int /*<<< orphan*/  blk_flush_restore_request (struct request*) ; 
 int /*<<< orphan*/  blk_kick_flush (struct request_queue*,struct blk_flush_queue*,unsigned int) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void blk_flush_complete_seq(struct request *rq,
				   struct blk_flush_queue *fq,
				   unsigned int seq, blk_status_t error)
{
	struct request_queue *q = rq->q;
	struct list_head *pending = &fq->flush_queue[fq->flush_pending_idx];
	unsigned int cmd_flags;

	BUG_ON(rq->flush.seq & seq);
	rq->flush.seq |= seq;
	cmd_flags = rq->cmd_flags;

	if (likely(!error))
		seq = blk_flush_cur_seq(rq);
	else
		seq = REQ_FSEQ_DONE;

	switch (seq) {
	case REQ_FSEQ_PREFLUSH:
	case REQ_FSEQ_POSTFLUSH:
		/* queue for flush */
		if (list_empty(pending))
			fq->flush_pending_since = jiffies;
		list_move_tail(&rq->flush.list, pending);
		break;

	case REQ_FSEQ_DATA:
		list_move_tail(&rq->flush.list, &fq->flush_data_in_flight);
		blk_flush_queue_rq(rq, true);
		break;

	case REQ_FSEQ_DONE:
		/*
		 * @rq was previously adjusted by blk_flush_issue() for
		 * flush sequencing and may already have gone through the
		 * flush data request completion path.  Restore @rq for
		 * normal completion and end it.
		 */
		BUG_ON(!list_empty(&rq->queuelist));
		list_del_init(&rq->flush.list);
		blk_flush_restore_request(rq);
		blk_mq_end_request(rq, error);
		break;

	default:
		BUG();
	}

	blk_kick_flush(q, fq, cmd_flags);
}