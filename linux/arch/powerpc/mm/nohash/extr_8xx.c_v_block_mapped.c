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
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 unsigned long IMMR_SIZE ; 
 unsigned long PAGE_OFFSET ; 
 unsigned long PHYS_IMMR_BASE ; 
 unsigned long VIRT_IMMR_BASE ; 
 scalar_t__ __map_without_ltlbs ; 
 unsigned long __pa (unsigned long) ; 
 unsigned long block_mapped_ram ; 

phys_addr_t v_block_mapped(unsigned long va)
{
	unsigned long p = PHYS_IMMR_BASE;

	if (__map_without_ltlbs)
		return 0;
	if (va >= VIRT_IMMR_BASE && va < VIRT_IMMR_BASE + IMMR_SIZE)
		return p + va - VIRT_IMMR_BASE;
	if (va >= PAGE_OFFSET && va < PAGE_OFFSET + block_mapped_ram)
		return __pa(va);
	return 0;
}