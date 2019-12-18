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
struct request_queue {int /*<<< orphan*/  q_usage_counter; int /*<<< orphan*/  sysfs_lock; scalar_t__ elevator; TYPE_1__* backing_dev_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  laptop_mode_wb_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_DEAD ; 
 int /*<<< orphan*/  QUEUE_FLAG_DYING ; 
 int /*<<< orphan*/  QUEUE_FLAG_NOMERGES ; 
 int /*<<< orphan*/  QUEUE_FLAG_NOXMERGES ; 
 int /*<<< orphan*/  blk_flush_integrity () ; 
 int /*<<< orphan*/  blk_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_exit_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_sched_free_requests (struct request_queue*) ; 
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_set_queue_dying (struct request_queue*) ; 
 int /*<<< orphan*/  blk_sync_queue (struct request_queue*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_is_mq (struct request_queue*) ; 
 int /*<<< orphan*/  rq_qos_exit (struct request_queue*) ; 

void blk_cleanup_queue(struct request_queue *q)
{
	/* mark @q DYING, no new request or merges will be allowed afterwards */
	mutex_lock(&q->sysfs_lock);
	blk_set_queue_dying(q);

	blk_queue_flag_set(QUEUE_FLAG_NOMERGES, q);
	blk_queue_flag_set(QUEUE_FLAG_NOXMERGES, q);
	blk_queue_flag_set(QUEUE_FLAG_DYING, q);
	mutex_unlock(&q->sysfs_lock);

	/*
	 * Drain all requests queued before DYING marking. Set DEAD flag to
	 * prevent that blk_mq_run_hw_queues() accesses the hardware queues
	 * after draining finished.
	 */
	blk_freeze_queue(q);

	rq_qos_exit(q);

	blk_queue_flag_set(QUEUE_FLAG_DEAD, q);

	/* for synchronous bio-based driver finish in-flight integrity i/o */
	blk_flush_integrity();

	/* @q won't process any more request, flush async actions */
	del_timer_sync(&q->backing_dev_info->laptop_mode_wb_timer);
	blk_sync_queue(q);

	if (queue_is_mq(q))
		blk_mq_exit_queue(q);

	/*
	 * In theory, request pool of sched_tags belongs to request queue.
	 * However, the current implementation requires tag_set for freeing
	 * requests, so free the pool now.
	 *
	 * Queue has become frozen, there can't be any in-queue requests, so
	 * it is safe to free requests now.
	 */
	mutex_lock(&q->sysfs_lock);
	if (q->elevator)
		blk_mq_sched_free_requests(q);
	mutex_unlock(&q->sysfs_lock);

	percpu_ref_exit(&q->q_usage_counter);

	/* @q is and will stay empty, shutdown and put */
	blk_put_queue(q);
}