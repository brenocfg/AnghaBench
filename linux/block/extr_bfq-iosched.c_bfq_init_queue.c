#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  node; int /*<<< orphan*/  queue_lock; struct elevator_queue* elevator; } ;
struct elevator_type {int dummy; } ;
struct elevator_queue {int /*<<< orphan*/  kobj; struct bfq_data* elevator_data; } ;
struct TYPE_6__ {int prio_changed; int /*<<< orphan*/  new_weight; } ;
struct TYPE_7__ {TYPE_2__ entity; int /*<<< orphan*/  new_ioprio; int /*<<< orphan*/  new_ioprio_class; int /*<<< orphan*/  ref; } ;
struct TYPE_5__ {int /*<<< orphan*/  function; } ;
struct bfq_data {int hw_tag; size_t nonrot_with_queueing; int bfq_requests_within_timer; int bfq_large_burst_thresh; int low_latency; int bfq_wr_coeff; int bfq_wr_max_softrt_rate; int rate_dur_prod; int peak_rate; int /*<<< orphan*/  root_group; TYPE_3__ oom_bfqq; int /*<<< orphan*/  lock; struct request_queue* queue; scalar_t__ wr_busy_queues; void* bfq_wr_min_inter_arr_async; void* bfq_wr_min_idle_time; scalar_t__ bfq_wr_max_time; void* bfq_wr_rt_max_time; void* bfq_burst_interval; int /*<<< orphan*/  bfq_timeout; int /*<<< orphan*/  bfq_slice_idle; int /*<<< orphan*/  bfq_back_penalty; int /*<<< orphan*/  bfq_back_max; void** bfq_fifo_expire; int /*<<< orphan*/  bfq_max_budget; int /*<<< orphan*/  burst_list; int /*<<< orphan*/  idle_list; int /*<<< orphan*/  active_list; scalar_t__ num_groups_with_pending_reqs; int /*<<< orphan*/  queue_weights_tree; TYPE_1__ idle_slice_timer; int /*<<< orphan*/  dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFQ_DEFAULT_QUEUE_IOPRIO ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOPRIO_CLASS_BE ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  bfq_back_max ; 
 int /*<<< orphan*/  bfq_back_penalty ; 
 int /*<<< orphan*/  bfq_clear_bfqq_just_created (TYPE_3__*) ; 
 int /*<<< orphan*/  bfq_create_group_hierarchy (struct bfq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_default_max_budget ; 
 void** bfq_fifo_expire ; 
 int /*<<< orphan*/  bfq_idle_slice_timer ; 
 int /*<<< orphan*/  bfq_init_bfqq (struct bfq_data*,TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_init_entity (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_init_root_group (int /*<<< orphan*/ ,struct bfq_data*) ; 
 int /*<<< orphan*/  bfq_ioprio_to_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_slice_idle ; 
 int /*<<< orphan*/  bfq_timeout ; 
 size_t blk_queue_nonrot (struct request_queue*) ; 
 struct elevator_queue* elevator_alloc (struct request_queue*,struct elevator_type*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bfq_data*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct bfq_data* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* msecs_to_jiffies (int) ; 
 int* ref_rate ; 
 int* ref_wr_duration ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbt_disable_default (struct request_queue*) ; 

__attribute__((used)) static int bfq_init_queue(struct request_queue *q, struct elevator_type *e)
{
	struct bfq_data *bfqd;
	struct elevator_queue *eq;

	eq = elevator_alloc(q, e);
	if (!eq)
		return -ENOMEM;

	bfqd = kzalloc_node(sizeof(*bfqd), GFP_KERNEL, q->node);
	if (!bfqd) {
		kobject_put(&eq->kobj);
		return -ENOMEM;
	}
	eq->elevator_data = bfqd;

	spin_lock_irq(&q->queue_lock);
	q->elevator = eq;
	spin_unlock_irq(&q->queue_lock);

	/*
	 * Our fallback bfqq if bfq_find_alloc_queue() runs into OOM issues.
	 * Grab a permanent reference to it, so that the normal code flow
	 * will not attempt to free it.
	 */
	bfq_init_bfqq(bfqd, &bfqd->oom_bfqq, NULL, 1, 0);
	bfqd->oom_bfqq.ref++;
	bfqd->oom_bfqq.new_ioprio = BFQ_DEFAULT_QUEUE_IOPRIO;
	bfqd->oom_bfqq.new_ioprio_class = IOPRIO_CLASS_BE;
	bfqd->oom_bfqq.entity.new_weight =
		bfq_ioprio_to_weight(bfqd->oom_bfqq.new_ioprio);

	/* oom_bfqq does not participate to bursts */
	bfq_clear_bfqq_just_created(&bfqd->oom_bfqq);

	/*
	 * Trigger weight initialization, according to ioprio, at the
	 * oom_bfqq's first activation. The oom_bfqq's ioprio and ioprio
	 * class won't be changed any more.
	 */
	bfqd->oom_bfqq.entity.prio_changed = 1;

	bfqd->queue = q;

	INIT_LIST_HEAD(&bfqd->dispatch);

	hrtimer_init(&bfqd->idle_slice_timer, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);
	bfqd->idle_slice_timer.function = bfq_idle_slice_timer;

	bfqd->queue_weights_tree = RB_ROOT_CACHED;
	bfqd->num_groups_with_pending_reqs = 0;

	INIT_LIST_HEAD(&bfqd->active_list);
	INIT_LIST_HEAD(&bfqd->idle_list);
	INIT_HLIST_HEAD(&bfqd->burst_list);

	bfqd->hw_tag = -1;
	bfqd->nonrot_with_queueing = blk_queue_nonrot(bfqd->queue);

	bfqd->bfq_max_budget = bfq_default_max_budget;

	bfqd->bfq_fifo_expire[0] = bfq_fifo_expire[0];
	bfqd->bfq_fifo_expire[1] = bfq_fifo_expire[1];
	bfqd->bfq_back_max = bfq_back_max;
	bfqd->bfq_back_penalty = bfq_back_penalty;
	bfqd->bfq_slice_idle = bfq_slice_idle;
	bfqd->bfq_timeout = bfq_timeout;

	bfqd->bfq_requests_within_timer = 120;

	bfqd->bfq_large_burst_thresh = 8;
	bfqd->bfq_burst_interval = msecs_to_jiffies(180);

	bfqd->low_latency = true;

	/*
	 * Trade-off between responsiveness and fairness.
	 */
	bfqd->bfq_wr_coeff = 30;
	bfqd->bfq_wr_rt_max_time = msecs_to_jiffies(300);
	bfqd->bfq_wr_max_time = 0;
	bfqd->bfq_wr_min_idle_time = msecs_to_jiffies(2000);
	bfqd->bfq_wr_min_inter_arr_async = msecs_to_jiffies(500);
	bfqd->bfq_wr_max_softrt_rate = 7000; /*
					      * Approximate rate required
					      * to playback or record a
					      * high-definition compressed
					      * video.
					      */
	bfqd->wr_busy_queues = 0;

	/*
	 * Begin by assuming, optimistically, that the device peak
	 * rate is equal to 2/3 of the highest reference rate.
	 */
	bfqd->rate_dur_prod = ref_rate[blk_queue_nonrot(bfqd->queue)] *
		ref_wr_duration[blk_queue_nonrot(bfqd->queue)];
	bfqd->peak_rate = ref_rate[blk_queue_nonrot(bfqd->queue)] * 2 / 3;

	spin_lock_init(&bfqd->lock);

	/*
	 * The invocation of the next bfq_create_group_hierarchy
	 * function is the head of a chain of function calls
	 * (bfq_create_group_hierarchy->blkcg_activate_policy->
	 * blk_mq_freeze_queue) that may lead to the invocation of the
	 * has_work hook function. For this reason,
	 * bfq_create_group_hierarchy is invoked only after all
	 * scheduler data has been initialized, apart from the fields
	 * that can be initialized only after invoking
	 * bfq_create_group_hierarchy. This, in particular, enables
	 * has_work to correctly return false. Of course, to avoid
	 * other inconsistencies, the blk-mq stack must then refrain
	 * from invoking further scheduler hooks before this init
	 * function is finished.
	 */
	bfqd->root_group = bfq_create_group_hierarchy(bfqd, q->node);
	if (!bfqd->root_group)
		goto out_free;
	bfq_init_root_group(bfqd->root_group, bfqd);
	bfq_init_entity(&bfqd->oom_bfqq.entity, bfqd->root_group);

	wbt_disable_default(q);
	return 0;

out_free:
	kfree(bfqd);
	kobject_put(&eq->kobj);
	return -ENOMEM;
}