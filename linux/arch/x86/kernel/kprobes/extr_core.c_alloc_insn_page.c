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
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* module_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_memory_ro (unsigned long,int) ; 
 int /*<<< orphan*/  set_memory_x (unsigned long,int) ; 
 int /*<<< orphan*/  set_vm_flush_reset_perms (void*) ; 

void *alloc_insn_page(void)
{
	void *page;

	page = module_alloc(PAGE_SIZE);
	if (!page)
		return NULL;

	set_vm_flush_reset_perms(page);
	/*
	 * First make the page read-only, and only then make it executable to
	 * prevent it from being W+X in between.
	 */
	set_memory_ro((unsigned long)page, 1);

	/*
	 * TODO: Once additional kernel code protection mechanisms are set, ensure
	 * that the page was not maliciously altered and it is still zeroed.
	 */
	set_memory_x((unsigned long)page, 1);

	return page;
}