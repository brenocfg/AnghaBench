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
typedef  int u32 ;
struct TYPE_2__ {int service; } ;
struct bfq_queue {TYPE_1__ entity; } ;
struct bfq_data {int bfq_max_budget; int /*<<< orphan*/  queue; int /*<<< orphan*/  last_budget_start; int /*<<< orphan*/  last_idling_start; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum bfqq_expiration { ____Placeholder_bfqq_expiration } bfqq_expiration ;

/* Variables and functions */
 int BFQQ_SEEKY (struct bfq_queue*) ; 
 unsigned long BFQ_MIN_TT ; 
 unsigned long NSEC_PER_MSEC ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  bfq_bfqq_sync (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*,int) ; 
 unsigned long bfq_slice_idle ; 
 scalar_t__ blk_queue_nonrot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bfq_bfqq_is_slow(struct bfq_data *bfqd, struct bfq_queue *bfqq,
				 bool compensate, enum bfqq_expiration reason,
				 unsigned long *delta_ms)
{
	ktime_t delta_ktime;
	u32 delta_usecs;
	bool slow = BFQQ_SEEKY(bfqq); /* if delta too short, use seekyness */

	if (!bfq_bfqq_sync(bfqq))
		return false;

	if (compensate)
		delta_ktime = bfqd->last_idling_start;
	else
		delta_ktime = ktime_get();
	delta_ktime = ktime_sub(delta_ktime, bfqd->last_budget_start);
	delta_usecs = ktime_to_us(delta_ktime);

	/* don't use too short time intervals */
	if (delta_usecs < 1000) {
		if (blk_queue_nonrot(bfqd->queue))
			 /*
			  * give same worst-case guarantees as idling
			  * for seeky
			  */
			*delta_ms = BFQ_MIN_TT / NSEC_PER_MSEC;
		else /* charge at least one seek */
			*delta_ms = bfq_slice_idle / NSEC_PER_MSEC;

		return slow;
	}

	*delta_ms = delta_usecs / USEC_PER_MSEC;

	/*
	 * Use only long (> 20ms) intervals to filter out excessive
	 * spikes in service rate estimation.
	 */
	if (delta_usecs > 20000) {
		/*
		 * Caveat for rotational devices: processes doing I/O
		 * in the slower disk zones tend to be slow(er) even
		 * if not seeky. In this respect, the estimated peak
		 * rate is likely to be an average over the disk
		 * surface. Accordingly, to not be too harsh with
		 * unlucky processes, a process is deemed slow only if
		 * its rate has been lower than half of the estimated
		 * peak rate.
		 */
		slow = bfqq->entity.service < bfqd->bfq_max_budget / 2;
	}

	bfq_log_bfqq(bfqd, bfqq, "bfq_bfqq_is_slow: slow %d", slow);

	return slow;
}