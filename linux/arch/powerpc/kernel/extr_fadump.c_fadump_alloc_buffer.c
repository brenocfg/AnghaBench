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
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SIZE ; 
 int __GFP_ZERO ; 
 void* alloc_pages_exact (unsigned long,int) ; 
 int /*<<< orphan*/  mark_page_reserved (struct page*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static void *fadump_alloc_buffer(unsigned long size)
{
	unsigned long count, i;
	struct page *page;
	void *vaddr;

	vaddr = alloc_pages_exact(size, GFP_KERNEL | __GFP_ZERO);
	if (!vaddr)
		return NULL;

	count = PAGE_ALIGN(size) / PAGE_SIZE;
	page = virt_to_page(vaddr);
	for (i = 0; i < count; i++)
		mark_page_reserved(page + i);
	return vaddr;
}