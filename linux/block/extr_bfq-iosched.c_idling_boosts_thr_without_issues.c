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
struct bfq_queue {int dummy; } ;
struct bfq_data {scalar_t__ wr_busy_queues; int /*<<< orphan*/  hw_tag; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFQQ_SEEKY (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_IO_bound (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_has_short_ttime (struct bfq_queue*) ; 
 int /*<<< orphan*/  blk_queue_nonrot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool idling_boosts_thr_without_issues(struct bfq_data *bfqd,
					     struct bfq_queue *bfqq)
{
	bool rot_without_queueing =
		!blk_queue_nonrot(bfqd->queue) && !bfqd->hw_tag,
		bfqq_sequential_and_IO_bound,
		idling_boosts_thr;

	bfqq_sequential_and_IO_bound = !BFQQ_SEEKY(bfqq) &&
		bfq_bfqq_IO_bound(bfqq) && bfq_bfqq_has_short_ttime(bfqq);

	/*
	 * The next variable takes into account the cases where idling
	 * boosts the throughput.
	 *
	 * The value of the variable is computed considering, first, that
	 * idling is virtually always beneficial for the throughput if:
	 * (a) the device is not NCQ-capable and rotational, or
	 * (b) regardless of the presence of NCQ, the device is rotational and
	 *     the request pattern for bfqq is I/O-bound and sequential, or
	 * (c) regardless of whether it is rotational, the device is
	 *     not NCQ-capable and the request pattern for bfqq is
	 *     I/O-bound and sequential.
	 *
	 * Secondly, and in contrast to the above item (b), idling an
	 * NCQ-capable flash-based device would not boost the
	 * throughput even with sequential I/O; rather it would lower
	 * the throughput in proportion to how fast the device
	 * is. Accordingly, the next variable is true if any of the
	 * above conditions (a), (b) or (c) is true, and, in
	 * particular, happens to be false if bfqd is an NCQ-capable
	 * flash-based device.
	 */
	idling_boosts_thr = rot_without_queueing ||
		((!blk_queue_nonrot(bfqd->queue) || !bfqd->hw_tag) &&
		 bfqq_sequential_and_IO_bound);

	/*
	 * The return value of this function is equal to that of
	 * idling_boosts_thr, unless a special case holds. In this
	 * special case, described below, idling may cause problems to
	 * weight-raised queues.
	 *
	 * When the request pool is saturated (e.g., in the presence
	 * of write hogs), if the processes associated with
	 * non-weight-raised queues ask for requests at a lower rate,
	 * then processes associated with weight-raised queues have a
	 * higher probability to get a request from the pool
	 * immediately (or at least soon) when they need one. Thus
	 * they have a higher probability to actually get a fraction
	 * of the device throughput proportional to their high
	 * weight. This is especially true with NCQ-capable drives,
	 * which enqueue several requests in advance, and further
	 * reorder internally-queued requests.
	 *
	 * For this reason, we force to false the return value if
	 * there are weight-raised busy queues. In this case, and if
	 * bfqq is not weight-raised, this guarantees that the device
	 * is not idled for bfqq (if, instead, bfqq is weight-raised,
	 * then idling will be guaranteed by another variable, see
	 * below). Combined with the timestamping rules of BFQ (see
	 * [1] for details), this behavior causes bfqq, and hence any
	 * sync non-weight-raised queue, to get a lower number of
	 * requests served, and thus to ask for a lower number of
	 * requests from the request pool, before the busy
	 * weight-raised queues get served again. This often mitigates
	 * starvation problems in the presence of heavy write
	 * workloads and NCQ, thereby guaranteeing a higher
	 * application and system responsiveness in these hostile
	 * scenarios.
	 */
	return idling_boosts_thr &&
		bfqd->wr_busy_queues == 0;
}