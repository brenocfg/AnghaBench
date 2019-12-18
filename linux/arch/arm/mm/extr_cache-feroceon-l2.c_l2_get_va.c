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
 unsigned long PAGE_SHIFT ; 
 unsigned long __phys_to_virt (unsigned long) ; 
 void* kmap_atomic_pfn (unsigned long) ; 

__attribute__((used)) static inline unsigned long l2_get_va(unsigned long paddr)
{
#ifdef CONFIG_HIGHMEM
	/*
	 * Because range ops can't be done on physical addresses,
	 * we simply install a virtual mapping for it only for the
	 * TLB lookup to occur, hence no need to flush the untouched
	 * memory mapping afterwards (note: a cache flush may happen
	 * in some circumstances depending on the path taken in kunmap_atomic).
	 */
	void *vaddr = kmap_atomic_pfn(paddr >> PAGE_SHIFT);
	return (unsigned long)vaddr + (paddr & ~PAGE_MASK);
#else
	return __phys_to_virt(paddr);
#endif
}