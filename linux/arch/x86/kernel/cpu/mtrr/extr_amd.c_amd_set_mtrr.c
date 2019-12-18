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
typedef  unsigned long u32 ;
typedef  int mtrr_type ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_K6_UWCCR ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static void
amd_set_mtrr(unsigned int reg, unsigned long base, unsigned long size, mtrr_type type)
{
	u32 regs[2];

	/*
	 * Low is MTRR0, High MTRR 1
	 */
	rdmsr(MSR_K6_UWCCR, regs[0], regs[1]);
	/*
	 * Blank to disable
	 */
	if (size == 0) {
		regs[reg] = 0;
	} else {
		/*
		 * Set the register to the base, the type (off by one) and an
		 * inverted bitmask of the size The size is the only odd
		 * bit. We are fed say 512K We invert this and we get 111 1111
		 * 1111 1011 but if you subtract one and invert you get the
		 * desired 111 1111 1111 1100 mask
		 *
		 *  But ~(x - 1) == ~x + 1 == -x. Two's complement rocks!
		 */
		regs[reg] = (-size >> (15 - PAGE_SHIFT) & 0x0001FFFC)
		    | (base << PAGE_SHIFT) | (type + 1);
	}

	/*
	 * The writeback rule is quite specific. See the manual. Its
	 * disable local interrupts, write back the cache, set the mtrr
	 */
	wbinvd();
	wrmsr(MSR_K6_UWCCR, regs[0], regs[1]);
}