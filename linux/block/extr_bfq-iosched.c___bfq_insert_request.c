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
struct TYPE_2__ {struct bfq_queue** priv; } ;
struct request {int /*<<< orphan*/  queuelist; scalar_t__ fifo_time; TYPE_1__ elv; } ;
struct bfq_queue {int /*<<< orphan*/  fifo; int /*<<< orphan*/  ref; int /*<<< orphan*/  allocated; } ;
struct bfq_data {scalar_t__* bfq_fifo_expire; } ;

/* Variables and functions */
 struct bfq_queue* RQ_BFQQ (struct request*) ; 
 int /*<<< orphan*/  RQ_BIC (struct request*) ; 
 int /*<<< orphan*/  bfq_add_request (struct request*) ; 
 scalar_t__ bfq_bfqq_wait_request (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_just_created (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_merge_bfqqs (struct bfq_data*,int /*<<< orphan*/ ,struct bfq_queue*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_put_queue (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_rq_enqueued (struct bfq_data*,struct bfq_queue*,struct request*) ; 
 struct bfq_queue* bfq_setup_cooperator (struct bfq_data*,struct bfq_queue*,struct request*,int) ; 
 int /*<<< orphan*/  bfq_update_has_short_ttime (struct bfq_data*,struct bfq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_update_io_seektime (struct bfq_data*,struct bfq_queue*,struct request*) ; 
 int /*<<< orphan*/  bfq_update_io_thinktime (struct bfq_data*,struct bfq_queue*) ; 
 struct bfq_queue* bic_to_bfqq (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t rq_is_sync (struct request*) ; 

__attribute__((used)) static bool __bfq_insert_request(struct bfq_data *bfqd, struct request *rq)
{
	struct bfq_queue *bfqq = RQ_BFQQ(rq),
		*new_bfqq = bfq_setup_cooperator(bfqd, bfqq, rq, true);
	bool waiting, idle_timer_disabled = false;

	if (new_bfqq) {
		/*
		 * Release the request's reference to the old bfqq
		 * and make sure one is taken to the shared queue.
		 */
		new_bfqq->allocated++;
		bfqq->allocated--;
		new_bfqq->ref++;
		/*
		 * If the bic associated with the process
		 * issuing this request still points to bfqq
		 * (and thus has not been already redirected
		 * to new_bfqq or even some other bfq_queue),
		 * then complete the merge and redirect it to
		 * new_bfqq.
		 */
		if (bic_to_bfqq(RQ_BIC(rq), 1) == bfqq)
			bfq_merge_bfqqs(bfqd, RQ_BIC(rq),
					bfqq, new_bfqq);

		bfq_clear_bfqq_just_created(bfqq);
		/*
		 * rq is about to be enqueued into new_bfqq,
		 * release rq reference on bfqq
		 */
		bfq_put_queue(bfqq);
		rq->elv.priv[1] = new_bfqq;
		bfqq = new_bfqq;
	}

	bfq_update_io_thinktime(bfqd, bfqq);
	bfq_update_has_short_ttime(bfqd, bfqq, RQ_BIC(rq));
	bfq_update_io_seektime(bfqd, bfqq, rq);

	waiting = bfqq && bfq_bfqq_wait_request(bfqq);
	bfq_add_request(rq);
	idle_timer_disabled = waiting && !bfq_bfqq_wait_request(bfqq);

	rq->fifo_time = ktime_get_ns() + bfqd->bfq_fifo_expire[rq_is_sync(rq)];
	list_add_tail(&rq->queuelist, &bfqq->fifo);

	bfq_rq_enqueued(bfqd, bfqq, rq);

	return idle_timer_disabled;
}