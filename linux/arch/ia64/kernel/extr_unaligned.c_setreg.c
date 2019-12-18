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
struct switch_stack {unsigned long ar_unat; unsigned long caller_unat; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,unsigned long,...) ; 
 scalar_t__ GR_IN_SW (unsigned long) ; 
 scalar_t__ GR_OFFS (unsigned long) ; 
 unsigned long IA64_FIRST_STACKED_GR ; 
 int /*<<< orphan*/  set_rse_reg (struct pt_regs*,unsigned long,unsigned long,int) ; 

__attribute__((used)) static void
setreg (unsigned long regnum, unsigned long val, int nat, struct pt_regs *regs)
{
	struct switch_stack *sw = (struct switch_stack *) regs - 1;
	unsigned long addr;
	unsigned long bitmask;
	unsigned long *unat;

	/*
	 * First takes care of stacked registers
	 */
	if (regnum >= IA64_FIRST_STACKED_GR) {
		set_rse_reg(regs, regnum, val, nat);
		return;
	}

	/*
	 * Using r0 as a target raises a General Exception fault which has higher priority
	 * than the Unaligned Reference fault.
	 */

	/*
	 * Now look at registers in [0-31] range and init correct UNAT
	 */
	if (GR_IN_SW(regnum)) {
		addr = (unsigned long)sw;
		unat = &sw->ar_unat;
	} else {
		addr = (unsigned long)regs;
		unat = &sw->caller_unat;
	}
	DPRINT("tmp_base=%lx switch_stack=%s offset=%d\n",
	       addr, unat==&sw->ar_unat ? "yes":"no", GR_OFFS(regnum));
	/*
	 * add offset from base of struct
	 * and do it !
	 */
	addr += GR_OFFS(regnum);

	*(unsigned long *)addr = val;

	/*
	 * We need to clear the corresponding UNAT bit to fully emulate the load
	 * UNAT bit_pos = GR[r3]{8:3} form EAS-2.4
	 */
	bitmask   = 1UL << (addr >> 3 & 0x3f);
	DPRINT("*0x%lx=0x%lx NaT=%d prev_unat @%p=%lx\n", addr, val, nat, (void *) unat, *unat);
	if (nat) {
		*unat |= bitmask;
	} else {
		*unat &= ~bitmask;
	}
	DPRINT("*0x%lx=0x%lx NaT=%d new unat: %p=%lx\n", addr, val, nat, (void *) unat,*unat);
}