#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ last_end_request; } ;
struct TYPE_3__ {int /*<<< orphan*/  rb_node; } ;
struct bfq_queue {int max_budget; int wr_coeff; int seek_history; void* soft_rt_next_start; void* split_time; void* wr_start_at_switch_to_srt; void* last_wr_start_finish; void* budget_timeout; int /*<<< orphan*/  pid; TYPE_2__ ttime; struct bfq_data* bfqd; scalar_t__ ref; int /*<<< orphan*/  woken_list; int /*<<< orphan*/  woken_list_node; int /*<<< orphan*/  burst_list_node; int /*<<< orphan*/  fifo; TYPE_1__ entity; } ;
struct bfq_io_cq {int dummy; } ;
struct bfq_data {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfq_class_idle (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_clear_bfqq_sync (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_IO_bound (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_has_short_ttime (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_just_created (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_sync (struct bfq_queue*) ; 
 int bfq_max_budget (struct bfq_data*) ; 
 int /*<<< orphan*/  bfq_set_next_ioprio_data (struct bfq_queue*,struct bfq_io_cq*) ; 
 void* bfq_smallest_from_now () ; 
 void* jiffies ; 
 scalar_t__ ktime_get_ns () ; 

__attribute__((used)) static void bfq_init_bfqq(struct bfq_data *bfqd, struct bfq_queue *bfqq,
			  struct bfq_io_cq *bic, pid_t pid, int is_sync)
{
	RB_CLEAR_NODE(&bfqq->entity.rb_node);
	INIT_LIST_HEAD(&bfqq->fifo);
	INIT_HLIST_NODE(&bfqq->burst_list_node);
	INIT_HLIST_NODE(&bfqq->woken_list_node);
	INIT_HLIST_HEAD(&bfqq->woken_list);

	bfqq->ref = 0;
	bfqq->bfqd = bfqd;

	if (bic)
		bfq_set_next_ioprio_data(bfqq, bic);

	if (is_sync) {
		/*
		 * No need to mark as has_short_ttime if in
		 * idle_class, because no device idling is performed
		 * for queues in idle class
		 */
		if (!bfq_class_idle(bfqq))
			/* tentatively mark as has_short_ttime */
			bfq_mark_bfqq_has_short_ttime(bfqq);
		bfq_mark_bfqq_sync(bfqq);
		bfq_mark_bfqq_just_created(bfqq);
	} else
		bfq_clear_bfqq_sync(bfqq);

	/* set end request to minus infinity from now */
	bfqq->ttime.last_end_request = ktime_get_ns() + 1;

	bfq_mark_bfqq_IO_bound(bfqq);

	bfqq->pid = pid;

	/* Tentative initial value to trade off between thr and lat */
	bfqq->max_budget = (2 * bfq_max_budget(bfqd)) / 3;
	bfqq->budget_timeout = bfq_smallest_from_now();

	bfqq->wr_coeff = 1;
	bfqq->last_wr_start_finish = jiffies;
	bfqq->wr_start_at_switch_to_srt = bfq_smallest_from_now();
	bfqq->split_time = bfq_smallest_from_now();

	/*
	 * To not forget the possibly high bandwidth consumed by a
	 * process/queue in the recent past,
	 * bfq_bfqq_softrt_next_start() returns a value at least equal
	 * to the current value of bfqq->soft_rt_next_start (see
	 * comments on bfq_bfqq_softrt_next_start).  Set
	 * soft_rt_next_start to now, to mean that bfqq has consumed
	 * no bandwidth so far.
	 */
	bfqq->soft_rt_next_start = jiffies;

	/* first request is almost certainly seeky */
	bfqq->seek_history = 1;
}