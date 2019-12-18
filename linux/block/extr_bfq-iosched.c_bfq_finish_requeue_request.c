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
struct TYPE_2__ {int /*<<< orphan*/ ** priv; int /*<<< orphan*/  icq; } ;
struct request {int rq_flags; TYPE_1__ elv; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  q; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  io_start_time_ns; int /*<<< orphan*/  start_time_ns; } ;
struct bfq_queue {struct bfq_data* bfqd; } ;
struct bfq_data {int /*<<< orphan*/  lock; struct request* waited_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int RQF_ELVPRIV ; 
 int RQF_STARTED ; 
 struct bfq_queue* RQ_BFQQ (struct request*) ; 
 int /*<<< orphan*/  bfq_completed_request (struct bfq_queue*,struct bfq_data*) ; 
 int /*<<< orphan*/  bfq_finish_requeue_request_body (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_remove_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  bfq_update_inject_limit (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfqg_stats_update_completion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfqg_stats_update_io_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfqq_group (struct bfq_queue*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void bfq_finish_requeue_request(struct request *rq)
{
	struct bfq_queue *bfqq = RQ_BFQQ(rq);
	struct bfq_data *bfqd;

	/*
	 * Requeue and finish hooks are invoked in blk-mq without
	 * checking whether the involved request is actually still
	 * referenced in the scheduler. To handle this fact, the
	 * following two checks make this function exit in case of
	 * spurious invocations, for which there is nothing to do.
	 *
	 * First, check whether rq has nothing to do with an elevator.
	 */
	if (unlikely(!(rq->rq_flags & RQF_ELVPRIV)))
		return;

	/*
	 * rq either is not associated with any icq, or is an already
	 * requeued request that has not (yet) been re-inserted into
	 * a bfq_queue.
	 */
	if (!rq->elv.icq || !bfqq)
		return;

	bfqd = bfqq->bfqd;

	if (rq->rq_flags & RQF_STARTED)
		bfqg_stats_update_completion(bfqq_group(bfqq),
					     rq->start_time_ns,
					     rq->io_start_time_ns,
					     rq->cmd_flags);

	if (likely(rq->rq_flags & RQF_STARTED)) {
		unsigned long flags;

		spin_lock_irqsave(&bfqd->lock, flags);

		if (rq == bfqd->waited_rq)
			bfq_update_inject_limit(bfqd, bfqq);

		bfq_completed_request(bfqq, bfqd);
		bfq_finish_requeue_request_body(bfqq);

		spin_unlock_irqrestore(&bfqd->lock, flags);
	} else {
		/*
		 * Request rq may be still/already in the scheduler,
		 * in which case we need to remove it (this should
		 * never happen in case of requeue). And we cannot
		 * defer such a check and removal, to avoid
		 * inconsistencies in the time interval from the end
		 * of this function to the start of the deferred work.
		 * This situation seems to occur only in process
		 * context, as a consequence of a merge. In the
		 * current version of the code, this implies that the
		 * lock is held.
		 */

		if (!RB_EMPTY_NODE(&rq->rb_node)) {
			bfq_remove_request(rq->q, rq);
			bfqg_stats_update_io_remove(bfqq_group(bfqq),
						    rq->cmd_flags);
		}
		bfq_finish_requeue_request_body(bfqq);
	}

	/*
	 * Reset private fields. In case of a requeue, this allows
	 * this function to correctly do nothing if it is spuriously
	 * invoked again on this same request (see the check at the
	 * beginning of the function). Probably, a better general
	 * design would be to prevent blk-mq from invoking the requeue
	 * or finish hooks of an elevator, for a request that is not
	 * referred by that elevator.
	 *
	 * Resetting the following fields would break the
	 * request-insertion logic if rq is re-inserted into a bfq
	 * internal queue, without a re-preparation. Here we assume
	 * that re-insertions of requeued requests, without
	 * re-preparation, can happen only for pass_through or at_head
	 * requests (which are not re-inserted into bfq internal
	 * queues).
	 */
	rq->elv.priv[0] = NULL;
	rq->elv.priv[1] = NULL;
}