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
typedef  scalar_t__ vm_offset_t ;
struct mem_region {scalar_t__ mr_start; scalar_t__ mr_size; } ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  ofw_mem_regions (struct mem_region*,int*,struct mem_region*,int*) ; 
 int /*<<< orphan*/  parse_drconf_memory (struct mem_region*,int*,struct mem_region*,int*) ; 

void
chrp_mem_regions(platform_t plat, struct mem_region *phys, int *physsz,
    struct mem_region *avail, int *availsz)
{
	vm_offset_t maxphysaddr;
	int i;

	ofw_mem_regions(phys, physsz, avail, availsz);
	parse_drconf_memory(phys, physsz, avail, availsz);

	/*
	 * On some firmwares (SLOF), some memory may be marked available that
	 * doesn't actually exist. This manifests as an extension of the last
	 * available segment past the end of physical memory, so truncate that
	 * one.
	 */
	maxphysaddr = 0;
	for (i = 0; i < *physsz; i++)
		if (phys[i].mr_start + phys[i].mr_size > maxphysaddr)
			maxphysaddr = phys[i].mr_start + phys[i].mr_size;

	for (i = 0; i < *availsz; i++)
		if (avail[i].mr_start + avail[i].mr_size > maxphysaddr)
			avail[i].mr_size = maxphysaddr - avail[i].mr_start;
}