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
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 unsigned long __phys_to_virt (unsigned long) ; 
 scalar_t__ kmap_atomic_pfn (unsigned long) ; 
 int /*<<< orphan*/  l2_unmap_va (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned long l2_map_va(unsigned long pa, unsigned long prev_va)
{
#ifdef CONFIG_HIGHMEM
	unsigned long va = prev_va & PAGE_MASK;
	unsigned long pa_offset = pa << (32 - PAGE_SHIFT);
	if (unlikely(pa_offset < (prev_va << (32 - PAGE_SHIFT)))) {
		/*
		 * Switching to a new page.  Because cache ops are
		 * using virtual addresses only, we must put a mapping
		 * in place for it.
		 */
		l2_unmap_va(prev_va);
		va = (unsigned long)kmap_atomic_pfn(pa >> PAGE_SHIFT);
	}
	return va + (pa_offset >> (32 - PAGE_SHIFT));
#else
	return __phys_to_virt(pa);
#endif
}