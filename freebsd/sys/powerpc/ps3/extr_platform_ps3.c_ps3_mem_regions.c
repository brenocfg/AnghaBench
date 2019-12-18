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
typedef  int /*<<< orphan*/  uint64_t ;
struct mem_region {int mr_size; scalar_t__ mr_start; } ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  lv1_allocate_memory (int,int,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lv1_get_logical_partition_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lv1_get_repository_node_value (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int lv1_repository_string (char*) ; 
 int /*<<< orphan*/  ofw_mem_regions (struct mem_region*,int*,struct mem_region*,int*) ; 
 int ps3_real_maxaddr (int /*<<< orphan*/ ) ; 

void
ps3_mem_regions(platform_t plat, struct mem_region *phys, int *physsz,
    struct mem_region *avail_regions, int *availsz)
{
	uint64_t lpar_id, junk;
	int i;

	/* Prefer device tree information if available */
	if (OF_finddevice("/") != -1) {
		ofw_mem_regions(phys, physsz, avail_regions, availsz);
	} else {
		/* Real mode memory region is first segment */
		phys[0].mr_start = 0;
		phys[0].mr_size = ps3_real_maxaddr(plat);
		*physsz = *availsz = 1;
		avail_regions[0] = phys[0];
	}

	/* Now get extended memory region */
	lv1_get_logical_partition_id(&lpar_id);
	lv1_get_repository_node_value(lpar_id,
	    lv1_repository_string("bi") >> 32,
	    lv1_repository_string("rgntotal"), 0, 0,
	    &phys[*physsz].mr_size, &junk);
	for (i = 0; i < *physsz; i++)
		phys[*physsz].mr_size -= phys[i].mr_size;

	/* Convert to maximum amount we can allocate in 16 MB pages */
	phys[*physsz].mr_size -= phys[*physsz].mr_size % (16*1024*1024);

	/* Allocate extended memory region */
	lv1_allocate_memory(phys[*physsz].mr_size, 24 /* 16 MB pages */,
	    0, 0x04 /* any address */, &phys[*physsz].mr_start, &junk);
	avail_regions[*availsz] = phys[*physsz];
	(*physsz)++;
	(*availsz)++;
}