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
 int /*<<< orphan*/  RIC_FLUSH_TLB ; 
 int /*<<< orphan*/  __tlbiel_va (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long mmu_get_ap (unsigned long) ; 

__attribute__((used)) static inline void __tlbiel_va_range(unsigned long start, unsigned long end,
				    unsigned long pid, unsigned long page_size,
				    unsigned long psize)
{
	unsigned long addr;
	unsigned long ap = mmu_get_ap(psize);

	for (addr = start; addr < end; addr += page_size)
		__tlbiel_va(addr, pid, ap, RIC_FLUSH_TLB);
}