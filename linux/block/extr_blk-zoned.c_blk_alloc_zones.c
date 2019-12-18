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
struct blk_zone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_ZONED_REPORT_MAX_ZONES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct blk_zone* kvcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 size_t min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct blk_zone *blk_alloc_zones(unsigned int *nr_zones)
{
	struct blk_zone *zones;
	size_t nrz = min(*nr_zones, BLK_ZONED_REPORT_MAX_ZONES);

	/*
	 * GFP_KERNEL here is meaningless as the caller task context has
	 * the PF_MEMALLOC_NOIO flag set in blk_revalidate_disk_zones()
	 * with memalloc_noio_save().
	 */
	zones = kvcalloc(nrz, sizeof(struct blk_zone), GFP_KERNEL);
	if (!zones) {
		*nr_zones = 0;
		return NULL;
	}

	*nr_zones = nrz;

	return zones;
}