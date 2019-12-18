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
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cd_info; int /*<<< orphan*/  disk; int /*<<< orphan*/  tag_set; int /*<<< orphan*/  gdrom_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDROM_DEV_NAME ; 
 int /*<<< orphan*/  HW_EVENT_GDROM_CMD ; 
 int /*<<< orphan*/  HW_EVENT_GDROM_DMA ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ gd ; 
 scalar_t__ gdrom_major ; 
 int /*<<< orphan*/  unregister_blkdev (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_cdrom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_gdrom(struct platform_device *devptr)
{
	blk_cleanup_queue(gd.gdrom_rq);
	blk_mq_free_tag_set(&gd.tag_set);
	free_irq(HW_EVENT_GDROM_CMD, &gd);
	free_irq(HW_EVENT_GDROM_DMA, &gd);
	del_gendisk(gd.disk);
	if (gdrom_major)
		unregister_blkdev(gdrom_major, GDROM_DEV_NAME);
	unregister_cdrom(gd.cd_info);

	return 0;
}