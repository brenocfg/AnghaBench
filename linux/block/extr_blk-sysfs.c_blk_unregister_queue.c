#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  sysfs_dir_lock; int /*<<< orphan*/  sysfs_lock; scalar_t__ elevator; int /*<<< orphan*/  kobj; } ;
struct gendisk {struct request_queue* queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 int /*<<< orphan*/  QUEUE_FLAG_REGISTERED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  blk_mq_unregister_dev (TYPE_1__*,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_registered (struct request_queue*) ; 
 int /*<<< orphan*/  blk_trace_remove_sysfs (TYPE_1__*) ; 
 TYPE_1__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  elv_unregister_queue (struct request_queue*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_is_mq (struct request_queue*) ; 

void blk_unregister_queue(struct gendisk *disk)
{
	struct request_queue *q = disk->queue;

	if (WARN_ON(!q))
		return;

	/* Return early if disk->queue was never registered. */
	if (!blk_queue_registered(q))
		return;

	/*
	 * Since sysfs_remove_dir() prevents adding new directory entries
	 * before removal of existing entries starts, protect against
	 * concurrent elv_iosched_store() calls.
	 */
	mutex_lock(&q->sysfs_lock);
	blk_queue_flag_clear(QUEUE_FLAG_REGISTERED, q);
	mutex_unlock(&q->sysfs_lock);

	mutex_lock(&q->sysfs_dir_lock);
	/*
	 * Remove the sysfs attributes before unregistering the queue data
	 * structures that can be modified through sysfs.
	 */
	if (queue_is_mq(q))
		blk_mq_unregister_dev(disk_to_dev(disk), q);

	kobject_uevent(&q->kobj, KOBJ_REMOVE);
	kobject_del(&q->kobj);
	blk_trace_remove_sysfs(disk_to_dev(disk));

	mutex_lock(&q->sysfs_lock);
	if (q->elevator)
		elv_unregister_queue(q);
	mutex_unlock(&q->sysfs_lock);
	mutex_unlock(&q->sysfs_dir_lock);

	kobject_put(&disk_to_dev(disk)->kobj);
}