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
 unsigned long PAGE_SHIFT ; 
 unsigned long PFN_ALIGN (int /*<<< orphan*/ ) ; 
 int _PAGE_NX ; 
 scalar_t__ __end_rodata ; 
 int __supported_pte_mask ; 
 int /*<<< orphan*/  _text ; 
 int /*<<< orphan*/  debug_checkwx () ; 
 int kernel_set_to_readonly ; 
 int /*<<< orphan*/  mark_nxdata_nx () ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  set_pages_ro (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_pages_rw (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

void mark_rodata_ro(void)
{
	unsigned long start = PFN_ALIGN(_text);
	unsigned long size = (unsigned long)__end_rodata - start;

	set_pages_ro(virt_to_page(start), size >> PAGE_SHIFT);
	pr_info("Write protecting kernel text and read-only data: %luk\n",
		size >> 10);

	kernel_set_to_readonly = 1;

#ifdef CONFIG_CPA_DEBUG
	pr_info("Testing CPA: Reverting %lx-%lx\n", start, start + size);
	set_pages_rw(virt_to_page(start), size >> PAGE_SHIFT);

	pr_info("Testing CPA: write protecting again\n");
	set_pages_ro(virt_to_page(start), size >> PAGE_SHIFT);
#endif
	mark_nxdata_nx();
	if (__supported_pte_mask & _PAGE_NX)
		debug_checkwx();
}