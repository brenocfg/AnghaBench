#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct block_device {TYPE_3__* bd_disk; TYPE_2__* bd_part; } ;
struct blk_zone {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {TYPE_1__* fops; } ;
struct TYPE_5__ {scalar_t__ nr_sects; } ;
struct TYPE_4__ {int /*<<< orphan*/  report_zones; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __blkdev_nr_zones (struct request_queue*,scalar_t__) ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  blk_queue_is_zoned (struct request_queue*) ; 
 int blk_report_zones (TYPE_3__*,scalar_t__,struct blk_zone*,unsigned int*) ; 
 int /*<<< orphan*/  blkdev_report_zone (struct block_device*,struct blk_zone*) ; 
 scalar_t__ get_start_sect (struct block_device*) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 

int blkdev_report_zones(struct block_device *bdev, sector_t sector,
			struct blk_zone *zones, unsigned int *nr_zones)
{
	struct request_queue *q = bdev_get_queue(bdev);
	unsigned int i, nrz;
	int ret;

	if (!blk_queue_is_zoned(q))
		return -EOPNOTSUPP;

	/*
	 * A block device that advertized itself as zoned must have a
	 * report_zones method. If it does not have one defined, the device
	 * driver has a bug. So warn about that.
	 */
	if (WARN_ON_ONCE(!bdev->bd_disk->fops->report_zones))
		return -EOPNOTSUPP;

	if (!*nr_zones || sector >= bdev->bd_part->nr_sects) {
		*nr_zones = 0;
		return 0;
	}

	nrz = min(*nr_zones,
		  __blkdev_nr_zones(q, bdev->bd_part->nr_sects - sector));
	ret = blk_report_zones(bdev->bd_disk, get_start_sect(bdev) + sector,
			       zones, &nrz);
	if (ret)
		return ret;

	for (i = 0; i < nrz; i++) {
		if (!blkdev_report_zone(bdev, zones))
			break;
		zones++;
	}

	*nr_zones = i;

	return 0;
}