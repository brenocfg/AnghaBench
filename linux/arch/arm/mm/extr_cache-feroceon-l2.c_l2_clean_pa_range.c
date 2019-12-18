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
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long l2_get_va (unsigned long) ; 
 int /*<<< orphan*/  l2_put_va (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 

__attribute__((used)) static inline void l2_clean_pa_range(unsigned long start, unsigned long end)
{
	unsigned long va_start, va_end, flags;

	/*
	 * Make sure 'start' and 'end' reference the same page, as
	 * L2 is PIPT and range operations only do a TLB lookup on
	 * the start address.
	 */
	BUG_ON((start ^ end) >> PAGE_SHIFT);

	va_start = l2_get_va(start);
	va_end = va_start + (end - start);
	raw_local_irq_save(flags);
	__asm__("mcr p15, 1, %0, c15, c9, 4\n\t"
		"mcr p15, 1, %1, c15, c9, 5"
		: : "r" (va_start), "r" (va_end));
	raw_local_irq_restore(flags);
	l2_put_va(va_start);
}