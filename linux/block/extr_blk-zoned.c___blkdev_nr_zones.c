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
struct request_queue {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int blk_queue_zone_sectors (struct request_queue*) ; 
 int ilog2 (int) ; 

__attribute__((used)) static inline unsigned int __blkdev_nr_zones(struct request_queue *q,
					     sector_t nr_sectors)
{
	sector_t zone_sectors = blk_queue_zone_sectors(q);

	return (nr_sectors + zone_sectors - 1) >> ilog2(zone_sectors);
}