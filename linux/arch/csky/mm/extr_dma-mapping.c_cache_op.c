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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 void* __va (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 unsigned long offset_in_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 struct page* phys_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cache_op(phys_addr_t paddr, size_t size,
			    void (*fn)(unsigned long start, unsigned long end))
{
	struct page *page    = phys_to_page(paddr);
	void *start          = __va(page_to_phys(page));
	unsigned long offset = offset_in_page(paddr);
	size_t left          = size;

	do {
		size_t len = left;

		if (offset + len > PAGE_SIZE)
			len = PAGE_SIZE - offset;

		if (PageHighMem(page)) {
			start = kmap_atomic(page);

			fn((unsigned long)start + offset,
					(unsigned long)start + offset + len);

			kunmap_atomic(start);
		} else {
			fn((unsigned long)start + offset,
					(unsigned long)start + offset + len);
		}
		offset = 0;

		page++;
		start += PAGE_SIZE;
		left -= len;
	} while (left);
}