#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hd_struct {int /*<<< orphan*/  partno; } ;
struct TYPE_9__ {scalar_t__ stamp; int /*<<< orphan*/  holder_dir; } ;
struct gendisk {int flags; TYPE_3__ part0; int /*<<< orphan*/  slave_dir; int /*<<< orphan*/  minors; TYPE_1__* queue; int /*<<< orphan*/  lookup_sem; } ;
struct disk_part_iter {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
 int DISK_PITER_INCL_EMPTY ; 
 int DISK_PITER_REVERSE ; 
 int GENHD_FL_HIDDEN ; 
 int GENHD_FL_UP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bdev_unhash_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdi_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_integrity_del (struct gendisk*) ; 
 int /*<<< orphan*/  blk_invalidate_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_unregister_queue (struct gendisk*) ; 
 int /*<<< orphan*/  blk_unregister_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * block_depr ; 
 int /*<<< orphan*/  delete_partition (struct gendisk*,int /*<<< orphan*/ ) ; 
 char* dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  disk_del_events (struct gendisk*) ; 
 int /*<<< orphan*/  disk_devt (struct gendisk*) ; 
 int /*<<< orphan*/  disk_part_iter_exit (struct disk_part_iter*) ; 
 int /*<<< orphan*/  disk_part_iter_init (struct disk_part_iter*,struct gendisk*,int) ; 
 struct hd_struct* disk_part_iter_next (struct disk_part_iter*) ; 
 TYPE_2__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invalidate_partition (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_devt (struct hd_struct*) ; 
 int /*<<< orphan*/  part_stat_set_all (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_memalloc_noio (TYPE_2__*,int) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_deprecated ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void del_gendisk(struct gendisk *disk)
{
	struct disk_part_iter piter;
	struct hd_struct *part;

	blk_integrity_del(disk);
	disk_del_events(disk);

	/*
	 * Block lookups of the disk until all bdevs are unhashed and the
	 * disk is marked as dead (GENHD_FL_UP cleared).
	 */
	down_write(&disk->lookup_sem);
	/* invalidate stuff */
	disk_part_iter_init(&piter, disk,
			     DISK_PITER_INCL_EMPTY | DISK_PITER_REVERSE);
	while ((part = disk_part_iter_next(&piter))) {
		invalidate_partition(disk, part->partno);
		bdev_unhash_inode(part_devt(part));
		delete_partition(disk, part->partno);
	}
	disk_part_iter_exit(&piter);

	invalidate_partition(disk, 0);
	bdev_unhash_inode(disk_devt(disk));
	set_capacity(disk, 0);
	disk->flags &= ~GENHD_FL_UP;
	up_write(&disk->lookup_sem);

	if (!(disk->flags & GENHD_FL_HIDDEN))
		sysfs_remove_link(&disk_to_dev(disk)->kobj, "bdi");
	if (disk->queue) {
		/*
		 * Unregister bdi before releasing device numbers (as they can
		 * get reused and we'd get clashes in sysfs).
		 */
		if (!(disk->flags & GENHD_FL_HIDDEN))
			bdi_unregister(disk->queue->backing_dev_info);
		blk_unregister_queue(disk);
	} else {
		WARN_ON(1);
	}

	if (!(disk->flags & GENHD_FL_HIDDEN))
		blk_unregister_region(disk_devt(disk), disk->minors);
	/*
	 * Remove gendisk pointer from idr so that it cannot be looked up
	 * while RCU period before freeing gendisk is running to prevent
	 * use-after-free issues. Note that the device number stays
	 * "in-use" until we really free the gendisk.
	 */
	blk_invalidate_devt(disk_devt(disk));

	kobject_put(disk->part0.holder_dir);
	kobject_put(disk->slave_dir);

	part_stat_set_all(&disk->part0, 0);
	disk->part0.stamp = 0;
	if (!sysfs_deprecated)
		sysfs_remove_link(block_depr, dev_name(disk_to_dev(disk)));
	pm_runtime_set_memalloc_noio(disk_to_dev(disk), false);
	device_del(disk_to_dev(disk));
}