#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gendisk {int flags; TYPE_1__* queue; scalar_t__ minors; scalar_t__ first_minor; scalar_t__ major; int /*<<< orphan*/  part0; } ;
struct device {int dummy; } ;
struct attribute_group {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_6__ {int /*<<< orphan*/  devt; } ;
struct TYPE_5__ {int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
 int GENHD_FL_EXT_DEVT ; 
 int GENHD_FL_HIDDEN ; 
 int GENHD_FL_NO_PART_SCAN ; 
 int GENHD_FL_SUPPRESS_PARTITION_INFO ; 
 int GENHD_FL_UP ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int bdi_register_owner (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int blk_alloc_devt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_get_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_integrity_add (struct gendisk*) ; 
 int /*<<< orphan*/  blk_register_queue (struct gendisk*) ; 
 int /*<<< orphan*/  blk_register_region (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gendisk*) ; 
 int /*<<< orphan*/  disk_add_events (struct gendisk*) ; 
 int /*<<< orphan*/  disk_alloc_events (struct gendisk*) ; 
 int /*<<< orphan*/  disk_devt (struct gendisk*) ; 
 TYPE_2__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  elevator_init_mq (TYPE_1__*) ; 
 int /*<<< orphan*/  exact_lock ; 
 int /*<<< orphan*/  exact_match ; 
 int /*<<< orphan*/  register_disk (struct device*,struct gendisk*,struct attribute_group const**) ; 

__attribute__((used)) static void __device_add_disk(struct device *parent, struct gendisk *disk,
			      const struct attribute_group **groups,
			      bool register_queue)
{
	dev_t devt;
	int retval;

	/*
	 * The disk queue should now be all set with enough information about
	 * the device for the elevator code to pick an adequate default
	 * elevator if one is needed, that is, for devices requesting queue
	 * registration.
	 */
	if (register_queue)
		elevator_init_mq(disk->queue);

	/* minors == 0 indicates to use ext devt from part0 and should
	 * be accompanied with EXT_DEVT flag.  Make sure all
	 * parameters make sense.
	 */
	WARN_ON(disk->minors && !(disk->major || disk->first_minor));
	WARN_ON(!disk->minors &&
		!(disk->flags & (GENHD_FL_EXT_DEVT | GENHD_FL_HIDDEN)));

	disk->flags |= GENHD_FL_UP;

	retval = blk_alloc_devt(&disk->part0, &devt);
	if (retval) {
		WARN_ON(1);
		return;
	}
	disk->major = MAJOR(devt);
	disk->first_minor = MINOR(devt);

	disk_alloc_events(disk);

	if (disk->flags & GENHD_FL_HIDDEN) {
		/*
		 * Don't let hidden disks show up in /proc/partitions,
		 * and don't bother scanning for partitions either.
		 */
		disk->flags |= GENHD_FL_SUPPRESS_PARTITION_INFO;
		disk->flags |= GENHD_FL_NO_PART_SCAN;
	} else {
		int ret;

		/* Register BDI before referencing it from bdev */
		disk_to_dev(disk)->devt = devt;
		ret = bdi_register_owner(disk->queue->backing_dev_info,
						disk_to_dev(disk));
		WARN_ON(ret);
		blk_register_region(disk_devt(disk), disk->minors, NULL,
				    exact_match, exact_lock, disk);
	}
	register_disk(parent, disk, groups);
	if (register_queue)
		blk_register_queue(disk);

	/*
	 * Take an extra ref on queue which will be put on disk_release()
	 * so that it sticks around as long as @disk is there.
	 */
	WARN_ON_ONCE(!blk_get_queue(disk->queue));

	disk_add_events(disk);
	blk_integrity_add(disk);
}