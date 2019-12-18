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
typedef  int phys_addr_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int phys_addr_valid (int) ; 

int valid_mmap_phys_addr_range(unsigned long pfn, size_t count)
{
	phys_addr_t addr = (phys_addr_t)pfn << PAGE_SHIFT;

	return phys_addr_valid(addr + count - 1);
}