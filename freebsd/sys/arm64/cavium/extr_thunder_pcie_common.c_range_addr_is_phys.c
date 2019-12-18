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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct pcie_range {scalar_t__ phys_base; scalar_t__ size; } ;

/* Variables and functions */
 int MAX_RANGES_TUPLES ; 

uint32_t
range_addr_is_phys(struct pcie_range *ranges, uint64_t addr, uint64_t size)
{
	struct pcie_range *r;
	int tuple;

	for (tuple = 0; tuple < MAX_RANGES_TUPLES; tuple++) {
		r = &ranges[tuple];
		if (addr >= r->phys_base &&
		    addr < (r->phys_base + r->size) &&
		    size < r->size) {
			/* Address is within Physical range */
			return (1);
		}
	}

	/* Address is outside Physical range */
	return (0);
}