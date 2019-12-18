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
typedef  scalar_t__ u32 ;
struct gendisk {int dummy; } ;
struct block_device {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 unsigned int bdev_zone_sectors (struct block_device*) ; 
 int /*<<< orphan*/  div_u64_rem (scalar_t__,unsigned int,scalar_t__*) ; 
 scalar_t__ get_capacity (struct gendisk*) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 

__attribute__((used)) static bool part_zone_aligned(struct gendisk *disk,
			      struct block_device *bdev,
			      sector_t from, sector_t size)
{
	unsigned int zone_sectors = bdev_zone_sectors(bdev);

	/*
	 * If this function is called, then the disk is a zoned block device
	 * (host-aware or host-managed). This can be detected even if the
	 * zoned block device support is disabled (CONFIG_BLK_DEV_ZONED not
	 * set). In this case, however, only host-aware devices will be seen
	 * as a block device is not created for host-managed devices. Without
	 * zoned block device support, host-aware drives can still be used as
	 * regular block devices (no zone operation) and their zone size will
	 * be reported as 0. Allow this case.
	 */
	if (!zone_sectors)
		return true;

	/*
	 * Check partition start and size alignement. If the drive has a
	 * smaller last runt zone, ignore it and allow the partition to
	 * use it. Check the zone size too: it should be a power of 2 number
	 * of sectors.
	 */
	if (WARN_ON_ONCE(!is_power_of_2(zone_sectors))) {
		u32 rem;

		div_u64_rem(from, zone_sectors, &rem);
		if (rem)
			return false;
		if ((from + size) < get_capacity(disk)) {
			div_u64_rem(size, zone_sectors, &rem);
			if (rem)
				return false;
		}

	} else {

		if (from & (zone_sectors - 1))
			return false;
		if ((from + size) < get_capacity(disk) &&
		    (size & (zone_sectors - 1)))
			return false;

	}

	return true;
}