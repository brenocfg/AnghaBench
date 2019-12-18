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
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  __flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  smp_cross_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  xcall_flush_tlb_kernel_range ; 

void smp_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	start &= PAGE_MASK;
	end    = PAGE_ALIGN(end);
	if (start != end) {
		smp_cross_call(&xcall_flush_tlb_kernel_range,
			       0, start, end);

		__flush_tlb_kernel_range(start, end);
	}
}