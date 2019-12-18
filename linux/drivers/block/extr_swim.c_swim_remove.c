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
struct swim_priv {int floppy_count; TYPE_2__* unit; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* disk; int /*<<< orphan*/  tag_set; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOPPY_MAJOR ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_unregister_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  floppy_eject (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct swim_priv*) ; 
 struct swim_priv* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int swim_remove(struct platform_device *dev)
{
	struct swim_priv *swd = platform_get_drvdata(dev);
	int drive;
	struct resource *res;

	blk_unregister_region(MKDEV(FLOPPY_MAJOR, 0), 256);

	for (drive = 0; drive < swd->floppy_count; drive++) {
		del_gendisk(swd->unit[drive].disk);
		blk_cleanup_queue(swd->unit[drive].disk->queue);
		blk_mq_free_tag_set(&swd->unit[drive].tag_set);
		put_disk(swd->unit[drive].disk);
	}

	unregister_blkdev(FLOPPY_MAJOR, "fd");

	/* eject floppies */

	for (drive = 0; drive < swd->floppy_count; drive++)
		floppy_eject(&swd->unit[drive]);

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (res)
		release_mem_region(res->start, resource_size(res));

	kfree(swd);

	return 0;
}