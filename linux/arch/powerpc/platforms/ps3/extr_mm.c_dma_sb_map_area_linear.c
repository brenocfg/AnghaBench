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
typedef  int /*<<< orphan*/  u64 ;
struct ps3_dma_region {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long __pa (unsigned long) ; 
 int /*<<< orphan*/  dma_sb_lpar_to_bus (struct ps3_dma_region*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_kernel_addr (unsigned long) ; 
 int /*<<< orphan*/  ps3_mm_phys_to_lpar (unsigned long) ; 

__attribute__((used)) static int dma_sb_map_area_linear(struct ps3_dma_region *r,
	unsigned long virt_addr, unsigned long len, dma_addr_t *bus_addr,
	u64 iopte_flag)
{
	unsigned long phys_addr = is_kernel_addr(virt_addr) ? __pa(virt_addr)
		: virt_addr;
	*bus_addr = dma_sb_lpar_to_bus(r, ps3_mm_phys_to_lpar(phys_addr));
	return 0;
}