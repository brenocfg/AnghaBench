#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct request_queue* q; int /*<<< orphan*/ * ops; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  default_depth; } ;
struct rq_wb {int wc; TYPE_2__ rqos; int /*<<< orphan*/  min_lat_nsec; int /*<<< orphan*/  cb; TYPE_1__ rq_depth; int /*<<< orphan*/  enable_state; int /*<<< orphan*/  win_nsec; int /*<<< orphan*/  last_issue; int /*<<< orphan*/  last_comp; int /*<<< orphan*/ * rq_wait; } ;
struct request_queue {int /*<<< orphan*/  queue_flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QUEUE_FLAG_WC ; 
 int /*<<< orphan*/  RQ_QOS_WBT ; 
 int /*<<< orphan*/  RWB_DEF_DEPTH ; 
 int /*<<< orphan*/  RWB_WINDOW_NSEC ; 
 int WBT_NUM_RWQ ; 
 int /*<<< orphan*/  WBT_STATE_ON_DEFAULT ; 
 int /*<<< orphan*/  __wbt_update_limits (struct rq_wb*) ; 
 int /*<<< orphan*/  blk_stat_add_callback (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_stat_alloc_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct rq_wb*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct rq_wb*) ; 
 struct rq_wb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_qos_add (struct request_queue*,TYPE_2__*) ; 
 int /*<<< orphan*/  rq_wait_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_timer_fn ; 
 int /*<<< orphan*/  wbt_data_dir ; 
 int /*<<< orphan*/  wbt_default_latency_nsec (struct request_queue*) ; 
 int /*<<< orphan*/  wbt_queue_depth_changed (TYPE_2__*) ; 
 int /*<<< orphan*/  wbt_rqos_ops ; 
 int /*<<< orphan*/  wbt_set_write_cache (struct request_queue*,int /*<<< orphan*/ ) ; 

int wbt_init(struct request_queue *q)
{
	struct rq_wb *rwb;
	int i;

	rwb = kzalloc(sizeof(*rwb), GFP_KERNEL);
	if (!rwb)
		return -ENOMEM;

	rwb->cb = blk_stat_alloc_callback(wb_timer_fn, wbt_data_dir, 2, rwb);
	if (!rwb->cb) {
		kfree(rwb);
		return -ENOMEM;
	}

	for (i = 0; i < WBT_NUM_RWQ; i++)
		rq_wait_init(&rwb->rq_wait[i]);

	rwb->rqos.id = RQ_QOS_WBT;
	rwb->rqos.ops = &wbt_rqos_ops;
	rwb->rqos.q = q;
	rwb->last_comp = rwb->last_issue = jiffies;
	rwb->win_nsec = RWB_WINDOW_NSEC;
	rwb->enable_state = WBT_STATE_ON_DEFAULT;
	rwb->wc = 1;
	rwb->rq_depth.default_depth = RWB_DEF_DEPTH;
	__wbt_update_limits(rwb);

	/*
	 * Assign rwb and add the stats callback.
	 */
	rq_qos_add(q, &rwb->rqos);
	blk_stat_add_callback(q, rwb->cb);

	rwb->min_lat_nsec = wbt_default_latency_nsec(q);

	wbt_queue_depth_changed(&rwb->rqos);
	wbt_set_write_cache(q, test_bit(QUEUE_FLAG_WC, &q->queue_flags));

	return 0;
}