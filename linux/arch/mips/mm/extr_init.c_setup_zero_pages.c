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
 int GFP_KERNEL ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,unsigned int) ; 
 scalar_t__ cpu_has_vce ; 
 scalar_t__ empty_zero_page ; 
 int /*<<< orphan*/  mark_page_reserved (struct page*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  split_page (struct page*,unsigned int) ; 
 struct page* virt_to_page (void*) ; 
 unsigned int zero_page_mask ; 

void setup_zero_pages(void)
{
	unsigned int order, i;
	struct page *page;

	if (cpu_has_vce)
		order = 3;
	else
		order = 0;

	empty_zero_page = __get_free_pages(GFP_KERNEL | __GFP_ZERO, order);
	if (!empty_zero_page)
		panic("Oh boy, that early out of memory?");

	page = virt_to_page((void *)empty_zero_page);
	split_page(page, order);
	for (i = 0; i < (1 << order); i++, page++)
		mark_page_reserved(page);

	zero_page_mask = ((PAGE_SIZE << order) - 1) & PAGE_MASK;
}