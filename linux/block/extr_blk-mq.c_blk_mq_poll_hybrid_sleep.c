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
struct request_queue {unsigned int poll_nsec; } ;
struct request {int rq_flags; } ;
struct hrtimer_sleeper {int /*<<< orphan*/  timer; scalar_t__ task; } ;
struct blk_mq_hw_ctx {int dummy; } ;
typedef  unsigned int ktime_t ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int HRTIMER_MODE_ABS ; 
 int HRTIMER_MODE_REL ; 
 scalar_t__ MQ_RQ_COMPLETE ; 
 int RQF_MQ_POLL_SLEPT ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 unsigned int blk_mq_poll_nsecs (struct request_queue*,struct blk_mq_hw_ctx*,struct request*) ; 
 scalar_t__ blk_mq_rq_state (struct request*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  destroy_hrtimer_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_init_sleeper_on_stack (struct hrtimer_sleeper*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hrtimer_set_expires (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  hrtimer_sleeper_start_expires (struct hrtimer_sleeper*,int) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool blk_mq_poll_hybrid_sleep(struct request_queue *q,
				     struct blk_mq_hw_ctx *hctx,
				     struct request *rq)
{
	struct hrtimer_sleeper hs;
	enum hrtimer_mode mode;
	unsigned int nsecs;
	ktime_t kt;

	if (rq->rq_flags & RQF_MQ_POLL_SLEPT)
		return false;

	/*
	 * If we get here, hybrid polling is enabled. Hence poll_nsec can be:
	 *
	 *  0:	use half of prev avg
	 * >0:	use this specific value
	 */
	if (q->poll_nsec > 0)
		nsecs = q->poll_nsec;
	else
		nsecs = blk_mq_poll_nsecs(q, hctx, rq);

	if (!nsecs)
		return false;

	rq->rq_flags |= RQF_MQ_POLL_SLEPT;

	/*
	 * This will be replaced with the stats tracking code, using
	 * 'avg_completion_time / 2' as the pre-sleep target.
	 */
	kt = nsecs;

	mode = HRTIMER_MODE_REL;
	hrtimer_init_sleeper_on_stack(&hs, CLOCK_MONOTONIC, mode);
	hrtimer_set_expires(&hs.timer, kt);

	do {
		if (blk_mq_rq_state(rq) == MQ_RQ_COMPLETE)
			break;
		set_current_state(TASK_UNINTERRUPTIBLE);
		hrtimer_sleeper_start_expires(&hs, mode);
		if (hs.task)
			io_schedule();
		hrtimer_cancel(&hs.timer);
		mode = HRTIMER_MODE_ABS;
	} while (hs.task && !signal_pending(current));

	__set_current_state(TASK_RUNNING);
	destroy_hrtimer_on_stack(&hs.timer);
	return true;
}