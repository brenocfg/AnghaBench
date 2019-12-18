#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {scalar_t__ id; int node; int /*<<< orphan*/  bio_split; TYPE_1__* backing_dev_info; int /*<<< orphan*/  stats; int /*<<< orphan*/  q_usage_counter; int /*<<< orphan*/  mq_freeze_lock; int /*<<< orphan*/  mq_freeze_wq; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  sysfs_dir_lock; int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  blk_trace_mutex; int /*<<< orphan*/  kobj; int /*<<< orphan*/  blkg_list; int /*<<< orphan*/  icq_list; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * last_merge; } ;
typedef  int gfp_t ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  laptop_mode_wb_timer; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  ra_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_CGROUP_WRITEBACK ; 
 int /*<<< orphan*/  BIOSET_NEED_BVECS ; 
 int /*<<< orphan*/  BIO_POOL_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERCPU_REF_INIT_ATOMIC ; 
 int /*<<< orphan*/  VM_READAHEAD_PAGES ; 
 int __GFP_ZERO ; 
 TYPE_1__* bdi_alloc_node (int,int) ; 
 int /*<<< orphan*/  bdi_put (TYPE_1__*) ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int bioset_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_alloc_queue_stats () ; 
 int /*<<< orphan*/  blk_free_queue_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_ida ; 
 int /*<<< orphan*/  blk_queue_ktype ; 
 int /*<<< orphan*/  blk_queue_usage_counter_release ; 
 int /*<<< orphan*/  blk_requestq_cachep ; 
 int /*<<< orphan*/  blk_rq_timed_out_timer ; 
 int /*<<< orphan*/  blk_timeout_work ; 
 scalar_t__ blkcg_init_queue (struct request_queue*) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct request_queue* kmem_cache_alloc_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  laptop_mode_timer_fn ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct request_queue *blk_alloc_queue_node(gfp_t gfp_mask, int node_id)
{
	struct request_queue *q;
	int ret;

	q = kmem_cache_alloc_node(blk_requestq_cachep,
				gfp_mask | __GFP_ZERO, node_id);
	if (!q)
		return NULL;

	q->last_merge = NULL;

	q->id = ida_simple_get(&blk_queue_ida, 0, 0, gfp_mask);
	if (q->id < 0)
		goto fail_q;

	ret = bioset_init(&q->bio_split, BIO_POOL_SIZE, 0, BIOSET_NEED_BVECS);
	if (ret)
		goto fail_id;

	q->backing_dev_info = bdi_alloc_node(gfp_mask, node_id);
	if (!q->backing_dev_info)
		goto fail_split;

	q->stats = blk_alloc_queue_stats();
	if (!q->stats)
		goto fail_stats;

	q->backing_dev_info->ra_pages = VM_READAHEAD_PAGES;
	q->backing_dev_info->capabilities = BDI_CAP_CGROUP_WRITEBACK;
	q->backing_dev_info->name = "block";
	q->node = node_id;

	timer_setup(&q->backing_dev_info->laptop_mode_wb_timer,
		    laptop_mode_timer_fn, 0);
	timer_setup(&q->timeout, blk_rq_timed_out_timer, 0);
	INIT_WORK(&q->timeout_work, blk_timeout_work);
	INIT_LIST_HEAD(&q->icq_list);
#ifdef CONFIG_BLK_CGROUP
	INIT_LIST_HEAD(&q->blkg_list);
#endif

	kobject_init(&q->kobj, &blk_queue_ktype);

#ifdef CONFIG_BLK_DEV_IO_TRACE
	mutex_init(&q->blk_trace_mutex);
#endif
	mutex_init(&q->sysfs_lock);
	mutex_init(&q->sysfs_dir_lock);
	spin_lock_init(&q->queue_lock);

	init_waitqueue_head(&q->mq_freeze_wq);
	mutex_init(&q->mq_freeze_lock);

	/*
	 * Init percpu_ref in atomic mode so that it's faster to shutdown.
	 * See blk_register_queue() for details.
	 */
	if (percpu_ref_init(&q->q_usage_counter,
				blk_queue_usage_counter_release,
				PERCPU_REF_INIT_ATOMIC, GFP_KERNEL))
		goto fail_bdi;

	if (blkcg_init_queue(q))
		goto fail_ref;

	return q;

fail_ref:
	percpu_ref_exit(&q->q_usage_counter);
fail_bdi:
	blk_free_queue_stats(q->stats);
fail_stats:
	bdi_put(q->backing_dev_info);
fail_split:
	bioset_exit(&q->bio_split);
fail_id:
	ida_simple_remove(&blk_queue_ida, q->id);
fail_q:
	kmem_cache_free(blk_requestq_cachep, q);
	return NULL;
}