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
struct request_queue {int dummy; } ;
struct request {scalar_t__ fifo_time; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  queuelist; } ;
struct bfq_queue {struct request* next_rq; } ;

/* Variables and functions */
 struct bfq_queue* bfq_init_rq (struct request*) ; 
 int /*<<< orphan*/  bfqg_stats_update_io_merged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfqq_group (struct bfq_queue*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_replace_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfq_requests_merged(struct request_queue *q, struct request *rq,
				struct request *next)
{
	struct bfq_queue *bfqq = bfq_init_rq(rq),
		*next_bfqq = bfq_init_rq(next);

	if (!bfqq)
		return;

	/*
	 * If next and rq belong to the same bfq_queue and next is older
	 * than rq, then reposition rq in the fifo (by substituting next
	 * with rq). Otherwise, if next and rq belong to different
	 * bfq_queues, never reposition rq: in fact, we would have to
	 * reposition it with respect to next's position in its own fifo,
	 * which would most certainly be too expensive with respect to
	 * the benefits.
	 */
	if (bfqq == next_bfqq &&
	    !list_empty(&rq->queuelist) && !list_empty(&next->queuelist) &&
	    next->fifo_time < rq->fifo_time) {
		list_del_init(&rq->queuelist);
		list_replace_init(&next->queuelist, &rq->queuelist);
		rq->fifo_time = next->fifo_time;
	}

	if (bfqq->next_rq == next)
		bfqq->next_rq = rq;

	bfqg_stats_update_io_merged(bfqq_group(bfqq), next->cmd_flags);
}