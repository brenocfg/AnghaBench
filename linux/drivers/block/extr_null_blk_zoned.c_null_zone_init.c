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
struct nullb_device {int zone_size; int zone_size_sects; int nr_zones; int zone_nr_conv; struct blk_zone* zones; scalar_t__ size; } ;
struct blk_zone {int start; int len; int wp; int /*<<< orphan*/  cond; int /*<<< orphan*/  type; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_ZONE_COND_EMPTY ; 
 int /*<<< orphan*/  BLK_ZONE_COND_NOT_WP ; 
 int /*<<< orphan*/  BLK_ZONE_TYPE_CONVENTIONAL ; 
 int /*<<< orphan*/  BLK_ZONE_TYPE_SEQWRITE_REQ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int SECTOR_SHIFT ; 
 int ZONE_SIZE_SHIFT ; 
 int __GFP_ZERO ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 struct blk_zone* kvmalloc_array (int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

int null_zone_init(struct nullb_device *dev)
{
	sector_t dev_size = (sector_t)dev->size * 1024 * 1024;
	sector_t sector = 0;
	unsigned int i;

	if (!is_power_of_2(dev->zone_size)) {
		pr_err("zone_size must be power-of-two\n");
		return -EINVAL;
	}

	dev->zone_size_sects = dev->zone_size << ZONE_SIZE_SHIFT;
	dev->nr_zones = dev_size >>
				(SECTOR_SHIFT + ilog2(dev->zone_size_sects));
	dev->zones = kvmalloc_array(dev->nr_zones, sizeof(struct blk_zone),
			GFP_KERNEL | __GFP_ZERO);
	if (!dev->zones)
		return -ENOMEM;

	if (dev->zone_nr_conv >= dev->nr_zones) {
		dev->zone_nr_conv = dev->nr_zones - 1;
		pr_info("changed the number of conventional zones to %u",
			dev->zone_nr_conv);
	}

	for (i = 0; i <  dev->zone_nr_conv; i++) {
		struct blk_zone *zone = &dev->zones[i];

		zone->start = sector;
		zone->len = dev->zone_size_sects;
		zone->wp = zone->start + zone->len;
		zone->type = BLK_ZONE_TYPE_CONVENTIONAL;
		zone->cond = BLK_ZONE_COND_NOT_WP;

		sector += dev->zone_size_sects;
	}

	for (i = dev->zone_nr_conv; i < dev->nr_zones; i++) {
		struct blk_zone *zone = &dev->zones[i];

		zone->start = zone->wp = sector;
		zone->len = dev->zone_size_sects;
		zone->type = BLK_ZONE_TYPE_SEQWRITE_REQ;
		zone->cond = BLK_ZONE_COND_EMPTY;

		sector += dev->zone_size_sects;
	}

	return 0;
}