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
struct gendisk {int dummy; } ;
struct block_device {scalar_t__ bd_invalidated; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  check_disk_size_change (struct gendisk*,struct block_device*,int) ; 
 TYPE_1__* disk_to_dev (struct gendisk*) ; 
 int drop_partitions (struct gendisk*,struct block_device*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 

int invalidate_partitions(struct gendisk *disk, struct block_device *bdev)
{
	int res;

	if (!bdev->bd_invalidated)
		return 0;

	res = drop_partitions(disk, bdev);
	if (res)
		return res;

	set_capacity(disk, 0);
	check_disk_size_change(disk, bdev, false);
	bdev->bd_invalidated = 0;
	/* tell userspace that the media / partition table may have changed */
	kobject_uevent(&disk_to_dev(disk)->kobj, KOBJ_CHANGE);

	return 0;
}