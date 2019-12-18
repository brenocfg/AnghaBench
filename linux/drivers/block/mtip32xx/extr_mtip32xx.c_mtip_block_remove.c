#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct driver_data {int /*<<< orphan*/  index; TYPE_2__* disk; int /*<<< orphan*/ * queue; int /*<<< orphan*/  tags; int /*<<< orphan*/  dd_flag; int /*<<< orphan*/ * bdev; TYPE_1__* pdev; TYPE_3__* port; int /*<<< orphan*/  sr; scalar_t__ mtip_svc_handler; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {int /*<<< orphan*/  svc_wait; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {scalar_t__ queue; int /*<<< orphan*/  disk_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_DDF_INIT_DONE_BIT ; 
 int /*<<< orphan*/  MTIP_PF_SVC_THD_STOP_BIT ; 
 int /*<<< orphan*/  MTIP_QUIESCE_IO_TIMEOUT_MS ; 
 int /*<<< orphan*/  bdput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_freeze_queue_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct driver_data*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* disk_to_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct kobject* kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  mtip_hw_debugfs_exit (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_exit (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_sysfs_exit (struct driver_data*,struct kobject*) ; 
 int /*<<< orphan*/  mtip_no_dev_cleanup ; 
 int /*<<< orphan*/  mtip_quiesce_io (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_standby_drive (struct driver_data*) ; 
 int /*<<< orphan*/  put_disk (TYPE_2__*) ; 
 int /*<<< orphan*/  rssd_index_ida ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtip_block_remove(struct driver_data *dd)
{
	struct kobject *kobj;

	mtip_hw_debugfs_exit(dd);

	if (dd->mtip_svc_handler) {
		set_bit(MTIP_PF_SVC_THD_STOP_BIT, &dd->port->flags);
		wake_up_interruptible(&dd->port->svc_wait);
		kthread_stop(dd->mtip_svc_handler);
	}

	/* Clean up the sysfs attributes, if created */
	if (test_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag)) {
		kobj = kobject_get(&disk_to_dev(dd->disk)->kobj);
		if (kobj) {
			mtip_hw_sysfs_exit(dd, kobj);
			kobject_put(kobj);
		}
	}

	if (!dd->sr) {
		/*
		 * Explicitly wait here for IOs to quiesce,
		 * as mtip_standby_drive usually won't wait for IOs.
		 */
		if (!mtip_quiesce_io(dd->port, MTIP_QUIESCE_IO_TIMEOUT_MS))
			mtip_standby_drive(dd);
	}
	else
		dev_info(&dd->pdev->dev, "device %s surprise removal\n",
						dd->disk->disk_name);

	blk_freeze_queue_start(dd->queue);
	blk_mq_quiesce_queue(dd->queue);
	blk_mq_tagset_busy_iter(&dd->tags, mtip_no_dev_cleanup, dd);
	blk_mq_unquiesce_queue(dd->queue);

	/*
	 * Delete our gendisk structure. This also removes the device
	 * from /dev
	 */
	if (dd->bdev) {
		bdput(dd->bdev);
		dd->bdev = NULL;
	}
	if (dd->disk) {
		if (test_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag))
			del_gendisk(dd->disk);
		if (dd->disk->queue) {
			blk_cleanup_queue(dd->queue);
			blk_mq_free_tag_set(&dd->tags);
			dd->queue = NULL;
		}
		put_disk(dd->disk);
	}
	dd->disk  = NULL;

	ida_free(&rssd_index_ida, dd->index);

	/* De-initialize the protocol layer. */
	mtip_hw_exit(dd);

	return 0;
}