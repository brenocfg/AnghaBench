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

/* Variables and functions */
 unsigned long MAX_DMA_ADDRESS ; 
 unsigned long PAGE_OFFSET ; 
 scalar_t__ high_memory ; 

__attribute__((used)) static inline bool __virt_addr_valid(unsigned long x)
{
	/*
	 * high_memory does not get immediately defined, and there
	 * are early callers of __pa() against PAGE_OFFSET
	 */
	if (!high_memory && x >= PAGE_OFFSET)
		return true;

	if (high_memory && x >= PAGE_OFFSET && x < (unsigned long)high_memory)
		return true;

	/*
	 * MAX_DMA_ADDRESS is a virtual address that may not correspond to an
	 * actual physical address. Enough code relies on __pa(MAX_DMA_ADDRESS)
	 * that we just need to work around it and always return true.
	 */
	if (x == MAX_DMA_ADDRESS)
		return true;

	return false;
}