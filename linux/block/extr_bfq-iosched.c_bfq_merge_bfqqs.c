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
struct TYPE_2__ {int prio_changed; } ;
struct bfq_queue {int pid; int wr_coeff; int /*<<< orphan*/ * bic; TYPE_1__ entity; int /*<<< orphan*/  wr_start_at_switch_to_srt; int /*<<< orphan*/  last_wr_start_finish; int /*<<< orphan*/  wr_cur_max_time; } ;
struct bfq_io_cq {int dummy; } ;
struct bfq_data {unsigned long wr_busy_queues; } ;

/* Variables and functions */
 scalar_t__ bfq_bfqq_IO_bound (struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_busy (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_save_state (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_IO_bound (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*,unsigned long) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_IO_bound (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_coop (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_put_queue (struct bfq_queue*) ; 
 int /*<<< orphan*/  bic_set_bfqq (struct bfq_io_cq*,struct bfq_queue*,int) ; 

__attribute__((used)) static void
bfq_merge_bfqqs(struct bfq_data *bfqd, struct bfq_io_cq *bic,
		struct bfq_queue *bfqq, struct bfq_queue *new_bfqq)
{
	bfq_log_bfqq(bfqd, bfqq, "merging with queue %lu",
		(unsigned long)new_bfqq->pid);
	/* Save weight raising and idle window of the merged queues */
	bfq_bfqq_save_state(bfqq);
	bfq_bfqq_save_state(new_bfqq);
	if (bfq_bfqq_IO_bound(bfqq))
		bfq_mark_bfqq_IO_bound(new_bfqq);
	bfq_clear_bfqq_IO_bound(bfqq);

	/*
	 * If bfqq is weight-raised, then let new_bfqq inherit
	 * weight-raising. To reduce false positives, neglect the case
	 * where bfqq has just been created, but has not yet made it
	 * to be weight-raised (which may happen because EQM may merge
	 * bfqq even before bfq_add_request is executed for the first
	 * time for bfqq). Handling this case would however be very
	 * easy, thanks to the flag just_created.
	 */
	if (new_bfqq->wr_coeff == 1 && bfqq->wr_coeff > 1) {
		new_bfqq->wr_coeff = bfqq->wr_coeff;
		new_bfqq->wr_cur_max_time = bfqq->wr_cur_max_time;
		new_bfqq->last_wr_start_finish = bfqq->last_wr_start_finish;
		new_bfqq->wr_start_at_switch_to_srt =
			bfqq->wr_start_at_switch_to_srt;
		if (bfq_bfqq_busy(new_bfqq))
			bfqd->wr_busy_queues++;
		new_bfqq->entity.prio_changed = 1;
	}

	if (bfqq->wr_coeff > 1) { /* bfqq has given its wr to new_bfqq */
		bfqq->wr_coeff = 1;
		bfqq->entity.prio_changed = 1;
		if (bfq_bfqq_busy(bfqq))
			bfqd->wr_busy_queues--;
	}

	bfq_log_bfqq(bfqd, new_bfqq, "merge_bfqqs: wr_busy %d",
		     bfqd->wr_busy_queues);

	/*
	 * Merge queues (that is, let bic redirect its requests to new_bfqq)
	 */
	bic_set_bfqq(bic, new_bfqq, 1);
	bfq_mark_bfqq_coop(new_bfqq);
	/*
	 * new_bfqq now belongs to at least two bics (it is a shared queue):
	 * set new_bfqq->bic to NULL. bfqq either:
	 * - does not belong to any bic any more, and hence bfqq->bic must
	 *   be set to NULL, or
	 * - is a queue whose owning bics have already been redirected to a
	 *   different queue, hence the queue is destined to not belong to
	 *   any bic soon and bfqq->bic is already NULL (therefore the next
	 *   assignment causes no harm).
	 */
	new_bfqq->bic = NULL;
	/*
	 * If the queue is shared, the pid is the pid of one of the associated
	 * processes. Which pid depends on the exact sequence of merge events
	 * the queue underwent. So printing such a pid is useless and confusing
	 * because it reports a random pid between those of the associated
	 * processes.
	 * We mark such a queue with a pid -1, and then print SHARED instead of
	 * a pid in logging messages.
	 */
	new_bfqq->pid = -1;
	bfqq->bic = NULL;
	/* release process reference to bfqq */
	bfq_put_queue(bfqq);
}