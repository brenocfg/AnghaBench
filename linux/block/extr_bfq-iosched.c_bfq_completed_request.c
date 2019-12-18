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
typedef  void* u64 ;
typedef  unsigned long u32 ;
struct TYPE_2__ {void* last_end_request; } ;
struct bfq_queue {scalar_t__ dispatched; scalar_t__ wr_coeff; int /*<<< orphan*/  sort_list; int /*<<< orphan*/  soft_rt_next_start; TYPE_1__ ttime; int /*<<< orphan*/  budget_timeout; } ;
struct bfq_data {void* last_completion; unsigned long last_rq_max_size; scalar_t__ bfq_wr_coeff; int /*<<< orphan*/  rq_in_driver; struct bfq_queue* in_service_queue; struct bfq_queue* last_completed_rq_bfqq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFQQE_BUDGET_TIMEOUT ; 
 int /*<<< orphan*/  BFQQE_NO_MORE_REQUESTS ; 
 unsigned long BFQ_MIN_TT ; 
 unsigned long BFQ_RATE_SHIFT ; 
 unsigned long NSEC_PER_USEC ; 
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfq_arm_slice_timer (struct bfq_data*) ; 
 int /*<<< orphan*/  bfq_better_to_idle (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_busy (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_expire (struct bfq_data*,struct bfq_queue*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bfq_bfqq_must_idle (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_softrt_next_start (struct bfq_data*,struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_softrt_update (struct bfq_queue*) ; 
 scalar_t__ bfq_may_expire_for_budg_timeout (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_schedule_dispatch (struct bfq_data*) ; 
 int /*<<< orphan*/  bfq_update_hw_tag (struct bfq_data*) ; 
 int /*<<< orphan*/  bfq_update_rate_reset (struct bfq_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfq_weights_tree_remove (struct bfq_data*,struct bfq_queue*) ; 
 unsigned long div_u64 (void*,unsigned long) ; 
 int /*<<< orphan*/  jiffies ; 
 void* ktime_get_ns () ; 

__attribute__((used)) static void bfq_completed_request(struct bfq_queue *bfqq, struct bfq_data *bfqd)
{
	u64 now_ns;
	u32 delta_us;

	bfq_update_hw_tag(bfqd);

	bfqd->rq_in_driver--;
	bfqq->dispatched--;

	if (!bfqq->dispatched && !bfq_bfqq_busy(bfqq)) {
		/*
		 * Set budget_timeout (which we overload to store the
		 * time at which the queue remains with no backlog and
		 * no outstanding request; used by the weight-raising
		 * mechanism).
		 */
		bfqq->budget_timeout = jiffies;

		bfq_weights_tree_remove(bfqd, bfqq);
	}

	now_ns = ktime_get_ns();

	bfqq->ttime.last_end_request = now_ns;

	/*
	 * Using us instead of ns, to get a reasonable precision in
	 * computing rate in next check.
	 */
	delta_us = div_u64(now_ns - bfqd->last_completion, NSEC_PER_USEC);

	/*
	 * If the request took rather long to complete, and, according
	 * to the maximum request size recorded, this completion latency
	 * implies that the request was certainly served at a very low
	 * rate (less than 1M sectors/sec), then the whole observation
	 * interval that lasts up to this time instant cannot be a
	 * valid time interval for computing a new peak rate.  Invoke
	 * bfq_update_rate_reset to have the following three steps
	 * taken:
	 * - close the observation interval at the last (previous)
	 *   request dispatch or completion
	 * - compute rate, if possible, for that observation interval
	 * - reset to zero samples, which will trigger a proper
	 *   re-initialization of the observation interval on next
	 *   dispatch
	 */
	if (delta_us > BFQ_MIN_TT/NSEC_PER_USEC &&
	   (bfqd->last_rq_max_size<<BFQ_RATE_SHIFT)/delta_us <
			1UL<<(BFQ_RATE_SHIFT - 10))
		bfq_update_rate_reset(bfqd, NULL);
	bfqd->last_completion = now_ns;
	bfqd->last_completed_rq_bfqq = bfqq;

	/*
	 * If we are waiting to discover whether the request pattern
	 * of the task associated with the queue is actually
	 * isochronous, and both requisites for this condition to hold
	 * are now satisfied, then compute soft_rt_next_start (see the
	 * comments on the function bfq_bfqq_softrt_next_start()). We
	 * do not compute soft_rt_next_start if bfqq is in interactive
	 * weight raising (see the comments in bfq_bfqq_expire() for
	 * an explanation). We schedule this delayed update when bfqq
	 * expires, if it still has in-flight requests.
	 */
	if (bfq_bfqq_softrt_update(bfqq) && bfqq->dispatched == 0 &&
	    RB_EMPTY_ROOT(&bfqq->sort_list) &&
	    bfqq->wr_coeff != bfqd->bfq_wr_coeff)
		bfqq->soft_rt_next_start =
			bfq_bfqq_softrt_next_start(bfqd, bfqq);

	/*
	 * If this is the in-service queue, check if it needs to be expired,
	 * or if we want to idle in case it has no pending requests.
	 */
	if (bfqd->in_service_queue == bfqq) {
		if (bfq_bfqq_must_idle(bfqq)) {
			if (bfqq->dispatched == 0)
				bfq_arm_slice_timer(bfqd);
			/*
			 * If we get here, we do not expire bfqq, even
			 * if bfqq was in budget timeout or had no
			 * more requests (as controlled in the next
			 * conditional instructions). The reason for
			 * not expiring bfqq is as follows.
			 *
			 * Here bfqq->dispatched > 0 holds, but
			 * bfq_bfqq_must_idle() returned true. This
			 * implies that, even if no request arrives
			 * for bfqq before bfqq->dispatched reaches 0,
			 * bfqq will, however, not be expired on the
			 * completion event that causes bfqq->dispatch
			 * to reach zero. In contrast, on this event,
			 * bfqq will start enjoying device idling
			 * (I/O-dispatch plugging).
			 *
			 * But, if we expired bfqq here, bfqq would
			 * not have the chance to enjoy device idling
			 * when bfqq->dispatched finally reaches
			 * zero. This would expose bfqq to violation
			 * of its reserved service guarantees.
			 */
			return;
		} else if (bfq_may_expire_for_budg_timeout(bfqq))
			bfq_bfqq_expire(bfqd, bfqq, false,
					BFQQE_BUDGET_TIMEOUT);
		else if (RB_EMPTY_ROOT(&bfqq->sort_list) &&
			 (bfqq->dispatched == 0 ||
			  !bfq_better_to_idle(bfqq)))
			bfq_bfqq_expire(bfqd, bfqq, false,
					BFQQE_NO_MORE_REQUESTS);
	}

	if (!bfqd->rq_in_driver)
		bfq_schedule_dispatch(bfqd);
}