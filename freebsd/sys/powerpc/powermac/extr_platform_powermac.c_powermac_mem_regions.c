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
struct mem_region {int mr_start; int mr_size; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  int /*<<< orphan*/  physacells ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  memoryprop ;
typedef  int cell_t ;

/* Variables and functions */
 int BUS_SPACE_MAXADDR_32BIT ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,int*,int) ; 
 int OF_parent (int) ; 
 int PHYS_AVAIL_SZ ; 

void
powermac_mem_regions(platform_t plat, struct mem_region *phys, int *physsz,
    struct mem_region *avail, int *availsz)
{
	phandle_t memory;
	cell_t memoryprop[PHYS_AVAIL_SZ * 2];
	ssize_t propsize, i, j;
	int physacells = 1;

	memory = OF_finddevice("/memory");
	if (memory == -1)
		memory = OF_finddevice("/memory@0");

	/* "reg" has variable #address-cells, but #size-cells is always 1 */
	OF_getprop(OF_parent(memory), "#address-cells", &physacells,
	    sizeof(physacells));

	propsize = OF_getprop(memory, "reg", memoryprop, sizeof(memoryprop));
	propsize /= sizeof(cell_t);
	for (i = 0, j = 0; i < propsize; i += physacells+1, j++) {
		phys[j].mr_start = memoryprop[i];
		if (physacells == 2) {
#ifndef __powerpc64__
			/* On 32-bit PPC, ignore regions starting above 4 GB */
			if (memoryprop[i] != 0) {
				j--;
				continue;
			}
#else
			phys[j].mr_start <<= 32;
#endif
			phys[j].mr_start |= memoryprop[i+1];
		}
		phys[j].mr_size = memoryprop[i + physacells];
	}
	*physsz = j;

	/* "available" always has #address-cells = 1 */
	propsize = OF_getprop(memory, "available", memoryprop,
	    sizeof(memoryprop));
	if (propsize <= 0) {
		for (i = 0; i < *physsz; i++) {
			avail[i].mr_start = phys[i].mr_start;
			avail[i].mr_size = phys[i].mr_size;
		}

		*availsz = *physsz;
	} else {
		propsize /= sizeof(cell_t);
		for (i = 0, j = 0; i < propsize; i += 2, j++) {
			avail[j].mr_start = memoryprop[i];
			avail[j].mr_size = memoryprop[i + 1];
		}

#ifdef __powerpc64__
		/* Add in regions above 4 GB to the available list */
		for (i = 0; i < *physsz; i++) {
			if (phys[i].mr_start > BUS_SPACE_MAXADDR_32BIT) {
				avail[j].mr_start = phys[i].mr_start;
				avail[j].mr_size = phys[i].mr_size;
				j++;
			}
		}
#endif
		*availsz = j;
	}
}