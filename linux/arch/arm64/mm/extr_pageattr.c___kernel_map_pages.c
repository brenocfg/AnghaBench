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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_pagealloc_enabled () ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  rodata_full ; 
 int /*<<< orphan*/  set_memory_valid (unsigned long,int,int) ; 

void __kernel_map_pages(struct page *page, int numpages, int enable)
{
	if (!debug_pagealloc_enabled() && !rodata_full)
		return;

	set_memory_valid((unsigned long)page_address(page), numpages, enable);
}