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
 int PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SIZE ; 
 void* fncpy (void*,void*,unsigned long) ; 
 void* omap_sram_push_address (unsigned long) ; 
 int /*<<< orphan*/  set_memory_ro (unsigned long,int) ; 
 int /*<<< orphan*/  set_memory_rw (unsigned long,int) ; 
 int /*<<< orphan*/  set_memory_x (unsigned long,int) ; 

void *omap_sram_push(void *funcp, unsigned long size)
{
	void *sram;
	unsigned long base;
	int pages;
	void *dst = NULL;

	sram = omap_sram_push_address(size);
	if (!sram)
		return NULL;

	base = (unsigned long)sram & PAGE_MASK;
	pages = PAGE_ALIGN(size) / PAGE_SIZE;

	set_memory_rw(base, pages);

	dst = fncpy(sram, funcp, size);

	set_memory_ro(base, pages);
	set_memory_x(base, pages);

	return dst;
}