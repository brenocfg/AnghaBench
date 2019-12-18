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
struct pt_regs {unsigned long nip; int msr; } ;

/* Variables and functions */
 int MSR_HV ; 
 int MSR_PR ; 
 int MSR_RI ; 
 scalar_t__ _stext ; 
 unsigned long end_real_trampolines ; 
 unsigned long end_virt_trampolines ; 
 unsigned long start_real_trampolines ; 
 unsigned long start_virt_trampolines ; 

void hv_nmi_check_nonrecoverable(struct pt_regs *regs)
{
#ifdef CONFIG_PPC_POWERNV
	unsigned long kbase = (unsigned long)_stext;
	unsigned long nip = regs->nip;

	if (!(regs->msr & MSR_RI))
		return;
	if (!(regs->msr & MSR_HV))
		return;
	if (regs->msr & MSR_PR)
		return;

	/*
	 * Now test if the interrupt has hit a range that may be using
	 * HSPRG1 without having RI=0 (i.e., an HSRR interrupt). The
	 * problem ranges all run un-relocated. Test real and virt modes
	 * at the same time by droping the high bit of the nip (virt mode
	 * entry points still have the +0x4000 offset).
	 */
	nip &= ~0xc000000000000000ULL;
	if ((nip >= 0x500 && nip < 0x600) || (nip >= 0x4500 && nip < 0x4600))
		goto nonrecoverable;
	if ((nip >= 0x980 && nip < 0xa00) || (nip >= 0x4980 && nip < 0x4a00))
		goto nonrecoverable;
	if ((nip >= 0xe00 && nip < 0xec0) || (nip >= 0x4e00 && nip < 0x4ec0))
		goto nonrecoverable;
	if ((nip >= 0xf80 && nip < 0xfa0) || (nip >= 0x4f80 && nip < 0x4fa0))
		goto nonrecoverable;

	/* Trampoline code runs un-relocated so subtract kbase. */
	if (nip >= (unsigned long)(start_real_trampolines - kbase) &&
			nip < (unsigned long)(end_real_trampolines - kbase))
		goto nonrecoverable;
	if (nip >= (unsigned long)(start_virt_trampolines - kbase) &&
			nip < (unsigned long)(end_virt_trampolines - kbase))
		goto nonrecoverable;
	return;

nonrecoverable:
	regs->msr &= ~MSR_RI;
#endif
}