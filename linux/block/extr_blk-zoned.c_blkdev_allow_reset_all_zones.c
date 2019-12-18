#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct block_device {int /*<<< orphan*/  bd_disk; int /*<<< orphan*/  bd_part; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  blk_queue_zone_resetall (int /*<<< orphan*/ ) ; 
 scalar_t__ get_capacity (int /*<<< orphan*/ ) ; 
 scalar_t__ get_start_sect (struct block_device*) ; 
 scalar_t__ part_nr_sects_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool blkdev_allow_reset_all_zones(struct block_device *bdev,
						sector_t nr_sectors)
{
	if (!blk_queue_zone_resetall(bdev_get_queue(bdev)))
		return false;

	if (nr_sectors != part_nr_sects_read(bdev->bd_part))
		return false;
	/*
	 * REQ_OP_ZONE_RESET_ALL can be executed only if the block device is
	 * the entire disk, that is, if the blocks device start offset is 0 and
	 * its capacity is the same as the entire disk.
	 */
	return get_start_sect(bdev) == 0 &&
	       part_nr_sects_read(bdev->bd_part) == get_capacity(bdev->bd_disk);
}