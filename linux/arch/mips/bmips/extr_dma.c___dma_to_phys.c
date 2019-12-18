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
struct device {int dummy; } ;
struct bmips_dma_range {scalar_t__ size; scalar_t__ parent_addr; scalar_t__ child_addr; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 struct bmips_dma_range* bmips_dma_ranges ; 

phys_addr_t __dma_to_phys(struct device *dev, dma_addr_t dma_addr)
{
	struct bmips_dma_range *r;

	for (r = bmips_dma_ranges; r && r->size; r++) {
		if (dma_addr >= r->parent_addr &&
		    dma_addr < (r->parent_addr + r->size))
			return dma_addr - r->parent_addr + r->child_addr;
	}
	return dma_addr;
}