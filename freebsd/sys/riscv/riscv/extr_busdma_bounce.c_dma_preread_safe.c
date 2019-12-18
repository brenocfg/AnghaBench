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
typedef  int vm_size_t ;
typedef  int vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_dcache_inv_range (int,int) ; 
 int /*<<< orphan*/  cpu_dcache_wb_range (int,int) ; 
 int dcache_line_size ; 

__attribute__((used)) static void
dma_preread_safe(vm_offset_t va, vm_size_t size)
{
	/*
	 * Write back any partial cachelines immediately before and
	 * after the DMA region.
	 */
	if (va & (dcache_line_size - 1))
		cpu_dcache_wb_range(va, 1);
	if ((va + size) & (dcache_line_size - 1))
		cpu_dcache_wb_range(va + size, 1);

	cpu_dcache_inv_range(va, size);
}