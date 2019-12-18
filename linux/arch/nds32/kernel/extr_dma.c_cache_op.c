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
typedef  unsigned int phys_addr_t ;

/* Variables and functions */
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 struct page* pfn_to_page (unsigned int) ; 
 scalar_t__ phys_to_virt (unsigned int) ; 

__attribute__((used)) static inline void cache_op(phys_addr_t paddr, size_t size,
		void (*fn)(unsigned long start, unsigned long end))
{
	struct page *page = pfn_to_page(paddr >> PAGE_SHIFT);
	unsigned offset = paddr & ~PAGE_MASK;
	size_t left = size;
	unsigned long start;

	do {
		size_t len = left;

		if (PageHighMem(page)) {
			void *addr;

			if (offset + len > PAGE_SIZE) {
				if (offset >= PAGE_SIZE) {
					page += offset >> PAGE_SHIFT;
					offset &= ~PAGE_MASK;
				}
				len = PAGE_SIZE - offset;
			}

			addr = kmap_atomic(page);
			start = (unsigned long)(addr + offset);
			fn(start, start + len);
			kunmap_atomic(addr);
		} else {
			start = (unsigned long)phys_to_virt(paddr);
			fn(start, start + size);
		}
		offset = 0;
		page++;
		left -= len;
	} while (left);
}