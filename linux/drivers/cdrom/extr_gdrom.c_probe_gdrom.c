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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct gdromtoc {int dummy; } ;
struct cdrom_device_info {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  events; int /*<<< orphan*/ * fops; } ;
struct TYPE_6__ {void* cd_info; TYPE_3__* disk; int /*<<< orphan*/  tag_set; int /*<<< orphan*/ * gdrom_rq; void* toc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_HIGH ; 
 int BLK_MQ_F_BLOCKING ; 
 int BLK_MQ_F_SHOULD_MERGE ; 
 int /*<<< orphan*/  DISK_EVENT_MEDIA_CHANGE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GDROM_DEV_NAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HW_EVENT_GDROM_CMD ; 
 int /*<<< orphan*/  HW_EVENT_GDROM_DMA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_disk (TYPE_3__*) ; 
 TYPE_3__* alloc_disk (int) ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * blk_mq_init_sq_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_3__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ gd ; 
 int /*<<< orphan*/  gdrom_bdops ; 
 int gdrom_execute_diagnostic () ; 
 scalar_t__ gdrom_major ; 
 int /*<<< orphan*/  gdrom_mq_ops ; 
 scalar_t__ gdrom_outputversion () ; 
 int gdrom_set_interrupt_handlers () ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/  probe_gdrom_setupcd () ; 
 int /*<<< orphan*/  probe_gdrom_setupdisk () ; 
 int probe_gdrom_setupqueue () ; 
 scalar_t__ register_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ register_cdrom (void*) ; 
 int /*<<< orphan*/  unregister_blkdev (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_gdrom(struct platform_device *devptr)
{
	int err;
	/* Start the device */
	if (gdrom_execute_diagnostic() != 1) {
		pr_warning("ATA Probe for GDROM failed\n");
		return -ENODEV;
	}
	/* Print out firmware ID */
	if (gdrom_outputversion())
		return -ENOMEM;
	/* Register GDROM */
	gdrom_major = register_blkdev(0, GDROM_DEV_NAME);
	if (gdrom_major <= 0)
		return gdrom_major;
	pr_info("Registered with major number %d\n",
		gdrom_major);
	/* Specify basic properties of drive */
	gd.cd_info = kzalloc(sizeof(struct cdrom_device_info), GFP_KERNEL);
	if (!gd.cd_info) {
		err = -ENOMEM;
		goto probe_fail_no_mem;
	}
	probe_gdrom_setupcd();
	gd.disk = alloc_disk(1);
	if (!gd.disk) {
		err = -ENODEV;
		goto probe_fail_no_disk;
	}
	probe_gdrom_setupdisk();
	if (register_cdrom(gd.cd_info)) {
		err = -ENODEV;
		goto probe_fail_cdrom_register;
	}
	gd.disk->fops = &gdrom_bdops;
	gd.disk->events = DISK_EVENT_MEDIA_CHANGE;
	/* latch on to the interrupt */
	err = gdrom_set_interrupt_handlers();
	if (err)
		goto probe_fail_cmdirq_register;

	gd.gdrom_rq = blk_mq_init_sq_queue(&gd.tag_set, &gdrom_mq_ops, 1,
				BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING);
	if (IS_ERR(gd.gdrom_rq)) {
		err = PTR_ERR(gd.gdrom_rq);
		gd.gdrom_rq = NULL;
		goto probe_fail_requestq;
	}

	blk_queue_bounce_limit(gd.gdrom_rq, BLK_BOUNCE_HIGH);

	err = probe_gdrom_setupqueue();
	if (err)
		goto probe_fail_toc;

	gd.toc = kzalloc(sizeof(struct gdromtoc), GFP_KERNEL);
	if (!gd.toc) {
		err = -ENOMEM;
		goto probe_fail_toc;
	}
	add_disk(gd.disk);
	return 0;

probe_fail_toc:
	blk_cleanup_queue(gd.gdrom_rq);
	blk_mq_free_tag_set(&gd.tag_set);
probe_fail_requestq:
	free_irq(HW_EVENT_GDROM_DMA, &gd);
	free_irq(HW_EVENT_GDROM_CMD, &gd);
probe_fail_cmdirq_register:
probe_fail_cdrom_register:
	del_gendisk(gd.disk);
probe_fail_no_disk:
	kfree(gd.cd_info);
probe_fail_no_mem:
	unregister_blkdev(gdrom_major, GDROM_DEV_NAME);
	gdrom_major = 0;
	pr_warning("Probe failed - error is 0x%X\n", err);
	return err;
}