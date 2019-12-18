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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ get_dcache_line_size () ; 
 scalar_t__ rounddown2 (scalar_t__,scalar_t__) ; 

void
cpu_flush_dcache(const void *ptr, size_t len)
{

	uint64_t cl_size;
	vm_offset_t addr, end;

	cl_size = get_dcache_line_size();

	/* Calculate end address to clean */
	end = (vm_offset_t)ptr + (vm_offset_t)len;
	/* Align start address to cache line */
	addr = (vm_offset_t)ptr;
	addr = rounddown2(addr, cl_size);

	for (; addr < end; addr += cl_size)
		__asm __volatile("dc	civac, %0" : : "r" (addr) : "memory");
	/* Full system DSB */
	__asm __volatile("dsb	sy" : : : "memory");
}