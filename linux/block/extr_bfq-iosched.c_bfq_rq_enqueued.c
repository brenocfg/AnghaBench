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
struct request {int cmd_flags; } ;
struct bfq_queue {int* queued; scalar_t__ last_request_pos; int /*<<< orphan*/  meta_pending; } ;
struct bfq_data {int /*<<< orphan*/  idle_slice_timer; struct bfq_queue* in_service_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFQQE_BUDGET_TIMEOUT ; 
 int REQ_META ; 
 int bfq_bfqq_budget_timeout (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_expire (struct bfq_data*,struct bfq_queue*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bfq_bfqq_wait_request (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_wait_request (struct bfq_queue*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ idling_boosts_thr_without_issues (struct bfq_data*,struct bfq_queue*) ; 
 size_t rq_is_sync (struct request*) ; 

__attribute__((used)) static void bfq_rq_enqueued(struct bfq_data *bfqd, struct bfq_queue *bfqq,
			    struct request *rq)
{
	if (rq->cmd_flags & REQ_META)
		bfqq->meta_pending++;

	bfqq->last_request_pos = blk_rq_pos(rq) + blk_rq_sectors(rq);

	if (bfqq == bfqd->in_service_queue && bfq_bfqq_wait_request(bfqq)) {
		bool small_req = bfqq->queued[rq_is_sync(rq)] == 1 &&
				 blk_rq_sectors(rq) < 32;
		bool budget_timeout = bfq_bfqq_budget_timeout(bfqq);

		/*
		 * There is just this request queued: if
		 * - the request is small, and
		 * - we are idling to boost throughput, and
		 * - the queue is not to be expired,
		 * then just exit.
		 *
		 * In this way, if the device is being idled to wait
		 * for a new request from the in-service queue, we
		 * avoid unplugging the device and committing the
		 * device to serve just a small request. In contrast
		 * we wait for the block layer to decide when to
		 * unplug the device: hopefully, new requests will be
		 * merged to this one quickly, then the device will be
		 * unplugged and larger requests will be dispatched.
		 */
		if (small_req && idling_boosts_thr_without_issues(bfqd, bfqq) &&
		    !budget_timeout)
			return;

		/*
		 * A large enough request arrived, or idling is being
		 * performed to preserve service guarantees, or
		 * finally the queue is to be expired: in all these
		 * cases disk idling is to be stopped, so clear
		 * wait_request flag and reset timer.
		 */
		bfq_clear_bfqq_wait_request(bfqq);
		hrtimer_try_to_cancel(&bfqd->idle_slice_timer);

		/*
		 * The queue is not empty, because a new request just
		 * arrived. Hence we can safely expire the queue, in
		 * case of budget timeout, without risking that the
		 * timestamps of the queue are not updated correctly.
		 * See [1] for more details.
		 */
		if (budget_timeout)
			bfq_bfqq_expire(bfqd, bfqq, false,
					BFQQE_BUDGET_TIMEOUT);
	}
}