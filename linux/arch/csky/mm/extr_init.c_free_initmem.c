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
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __init_begin ; 
 int /*<<< orphan*/  __init_end ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  init_page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int /*<<< orphan*/  totalram_pages_inc () ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

void free_initmem(void)
{
	unsigned long addr;

	addr = (unsigned long) &__init_begin;

	while (addr < (unsigned long) &__init_end) {
		ClearPageReserved(virt_to_page(addr));
		init_page_count(virt_to_page(addr));
		free_page(addr);
		totalram_pages_inc();
		addr += PAGE_SIZE;
	}

	pr_info("Freeing unused kernel memory: %dk freed\n",
	((unsigned int)&__init_end - (unsigned int)&__init_begin) >> 10);
}