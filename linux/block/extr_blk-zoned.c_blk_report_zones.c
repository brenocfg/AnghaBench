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
struct request_queue {int dummy; } ;
struct gendisk {TYPE_1__* fops; struct request_queue* queue; } ;
struct blk_zone {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int (* report_zones ) (struct gendisk*,scalar_t__,struct blk_zone*,unsigned int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int blk_queue_zone_sectors (struct request_queue*) ; 
 scalar_t__ get_capacity (struct gendisk*) ; 
 int stub1 (struct gendisk*,scalar_t__,struct blk_zone*,unsigned int*) ; 

__attribute__((used)) static int blk_report_zones(struct gendisk *disk, sector_t sector,
			    struct blk_zone *zones, unsigned int *nr_zones)
{
	struct request_queue *q = disk->queue;
	unsigned int z = 0, n, nrz = *nr_zones;
	sector_t capacity = get_capacity(disk);
	int ret;

	while (z < nrz && sector < capacity) {
		n = nrz - z;
		ret = disk->fops->report_zones(disk, sector, &zones[z], &n);
		if (ret)
			return ret;
		if (!n)
			break;
		sector += blk_queue_zone_sectors(q) * n;
		z += n;
	}

	WARN_ON(z > *nr_zones);
	*nr_zones = z;

	return 0;
}