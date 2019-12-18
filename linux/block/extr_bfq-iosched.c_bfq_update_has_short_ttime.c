#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ttime_mean; int /*<<< orphan*/  ttime_samples; } ;
struct bfq_queue {scalar_t__ last_serv_time_ns; scalar_t__ decrease_time_jif; TYPE_3__ ttime; scalar_t__ split_time; } ;
struct TYPE_5__ {TYPE_1__* ioc; } ;
struct bfq_io_cq {TYPE_2__ icq; } ;
struct bfq_data {scalar_t__ bfq_slice_idle; scalar_t__ bfq_wr_min_idle_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  active_ref; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int bfq_bfqq_has_short_ttime (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_sync (struct bfq_queue*) ; 
 scalar_t__ bfq_class_idle (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_has_short_ttime (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_has_short_ttime (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_reset_inject_limit (struct bfq_data*,struct bfq_queue*) ; 
 scalar_t__ bfq_sample_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ time_is_after_eq_jiffies (scalar_t__) ; 
 scalar_t__ time_is_before_eq_jiffies (scalar_t__) ; 

__attribute__((used)) static void bfq_update_has_short_ttime(struct bfq_data *bfqd,
				       struct bfq_queue *bfqq,
				       struct bfq_io_cq *bic)
{
	bool has_short_ttime = true, state_changed;

	/*
	 * No need to update has_short_ttime if bfqq is async or in
	 * idle io prio class, or if bfq_slice_idle is zero, because
	 * no device idling is performed for bfqq in this case.
	 */
	if (!bfq_bfqq_sync(bfqq) || bfq_class_idle(bfqq) ||
	    bfqd->bfq_slice_idle == 0)
		return;

	/* Idle window just restored, statistics are meaningless. */
	if (time_is_after_eq_jiffies(bfqq->split_time +
				     bfqd->bfq_wr_min_idle_time))
		return;

	/* Think time is infinite if no process is linked to
	 * bfqq. Otherwise check average think time to
	 * decide whether to mark as has_short_ttime
	 */
	if (atomic_read(&bic->icq.ioc->active_ref) == 0 ||
	    (bfq_sample_valid(bfqq->ttime.ttime_samples) &&
	     bfqq->ttime.ttime_mean > bfqd->bfq_slice_idle))
		has_short_ttime = false;

	state_changed = has_short_ttime != bfq_bfqq_has_short_ttime(bfqq);

	if (has_short_ttime)
		bfq_mark_bfqq_has_short_ttime(bfqq);
	else
		bfq_clear_bfqq_has_short_ttime(bfqq);

	/*
	 * Until the base value for the total service time gets
	 * finally computed for bfqq, the inject limit does depend on
	 * the think-time state (short|long). In particular, the limit
	 * is 0 or 1 if the think time is deemed, respectively, as
	 * short or long (details in the comments in
	 * bfq_update_inject_limit()). Accordingly, the next
	 * instructions reset the inject limit if the think-time state
	 * has changed and the above base value is still to be
	 * computed.
	 *
	 * However, the reset is performed only if more than 100 ms
	 * have elapsed since the last update of the inject limit, or
	 * (inclusive) if the change is from short to long think
	 * time. The reason for this waiting is as follows.
	 *
	 * bfqq may have a long think time because of a
	 * synchronization with some other queue, i.e., because the
	 * I/O of some other queue may need to be completed for bfqq
	 * to receive new I/O. Details in the comments on the choice
	 * of the queue for injection in bfq_select_queue().
	 *
	 * As stressed in those comments, if such a synchronization is
	 * actually in place, then, without injection on bfqq, the
	 * blocking I/O cannot happen to served while bfqq is in
	 * service. As a consequence, if bfqq is granted
	 * I/O-dispatch-plugging, then bfqq remains empty, and no I/O
	 * is dispatched, until the idle timeout fires. This is likely
	 * to result in lower bandwidth and higher latencies for bfqq,
	 * and in a severe loss of total throughput.
	 *
	 * On the opposite end, a non-zero inject limit may allow the
	 * I/O that blocks bfqq to be executed soon, and therefore
	 * bfqq to receive new I/O soon.
	 *
	 * But, if the blocking gets actually eliminated, then the
	 * next think-time sample for bfqq may be very low. This in
	 * turn may cause bfqq's think time to be deemed
	 * short. Without the 100 ms barrier, this new state change
	 * would cause the body of the next if to be executed
	 * immediately. But this would set to 0 the inject
	 * limit. Without injection, the blocking I/O would cause the
	 * think time of bfqq to become long again, and therefore the
	 * inject limit to be raised again, and so on. The only effect
	 * of such a steady oscillation between the two think-time
	 * states would be to prevent effective injection on bfqq.
	 *
	 * In contrast, if the inject limit is not reset during such a
	 * long time interval as 100 ms, then the number of short
	 * think time samples can grow significantly before the reset
	 * is performed. As a consequence, the think time state can
	 * become stable before the reset. Therefore there will be no
	 * state change when the 100 ms elapse, and no reset of the
	 * inject limit. The inject limit remains steadily equal to 1
	 * both during and after the 100 ms. So injection can be
	 * performed at all times, and throughput gets boosted.
	 *
	 * An inject limit equal to 1 is however in conflict, in
	 * general, with the fact that the think time of bfqq is
	 * short, because injection may be likely to delay bfqq's I/O
	 * (as explained in the comments in
	 * bfq_update_inject_limit()). But this does not happen in
	 * this special case, because bfqq's low think time is due to
	 * an effective handling of a synchronization, through
	 * injection. In this special case, bfqq's I/O does not get
	 * delayed by injection; on the contrary, bfqq's I/O is
	 * brought forward, because it is not blocked for
	 * milliseconds.
	 *
	 * In addition, serving the blocking I/O much sooner, and much
	 * more frequently than once per I/O-plugging timeout, makes
	 * it much quicker to detect a waker queue (the concept of
	 * waker queue is defined in the comments in
	 * bfq_add_request()). This makes it possible to start sooner
	 * to boost throughput more effectively, by injecting the I/O
	 * of the waker queue unconditionally on every
	 * bfq_dispatch_request().
	 *
	 * One last, important benefit of not resetting the inject
	 * limit before 100 ms is that, during this time interval, the
	 * base value for the total service time is likely to get
	 * finally computed for bfqq, freeing the inject limit from
	 * its relation with the think time.
	 */
	if (state_changed && bfqq->last_serv_time_ns == 0 &&
	    (time_is_before_eq_jiffies(bfqq->decrease_time_jif +
				      msecs_to_jiffies(100)) ||
	     !has_short_ttime))
		bfq_reset_inject_limit(bfqd, bfqq);
}