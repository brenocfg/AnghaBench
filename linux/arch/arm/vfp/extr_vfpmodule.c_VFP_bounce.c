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
typedef  int u32 ;
struct pt_regs {int ARM_pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPEXC ; 
 int FPEXC_DEX ; 
 int FPEXC_EX ; 
 int FPEXC_FP2V ; 
 int FPEXC_LENGTH_BIT ; 
 int FPEXC_LENGTH_MASK ; 
 int FPEXC_TRAP_MASK ; 
 int FPEXC_VV ; 
 int /*<<< orphan*/  FPINST ; 
 int /*<<< orphan*/  FPINST2 ; 
 int /*<<< orphan*/  FPSCR ; 
 int FPSCR_IXE ; 
 int FPSCR_LENGTH_BIT ; 
 int FPSCR_LENGTH_MASK ; 
 int /*<<< orphan*/  FPSID ; 
 int FPSID_ARCH_BIT ; 
 int FPSID_ARCH_MASK ; 
 int VFP_EXCEPTION_ERROR ; 
 int /*<<< orphan*/  barrier () ; 
 int fmrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int vfp_emulate_instruction (int,int,struct pt_regs*) ; 
 int /*<<< orphan*/  vfp_raise_exceptions (int,int,int,struct pt_regs*) ; 

void VFP_bounce(u32 trigger, u32 fpexc, struct pt_regs *regs)
{
	u32 fpscr, orig_fpscr, fpsid, exceptions;

	pr_debug("VFP: bounce: trigger %08x fpexc %08x\n", trigger, fpexc);

	/*
	 * At this point, FPEXC can have the following configuration:
	 *
	 *  EX DEX IXE
	 *  0   1   x   - synchronous exception
	 *  1   x   0   - asynchronous exception
	 *  1   x   1   - sychronous on VFP subarch 1 and asynchronous on later
	 *  0   0   1   - synchronous on VFP9 (non-standard subarch 1
	 *                implementation), undefined otherwise
	 *
	 * Clear various bits and enable access to the VFP so we can
	 * handle the bounce.
	 */
	fmxr(FPEXC, fpexc & ~(FPEXC_EX|FPEXC_DEX|FPEXC_FP2V|FPEXC_VV|FPEXC_TRAP_MASK));

	fpsid = fmrx(FPSID);
	orig_fpscr = fpscr = fmrx(FPSCR);

	/*
	 * Check for the special VFP subarch 1 and FPSCR.IXE bit case
	 */
	if ((fpsid & FPSID_ARCH_MASK) == (1 << FPSID_ARCH_BIT)
	    && (fpscr & FPSCR_IXE)) {
		/*
		 * Synchronous exception, emulate the trigger instruction
		 */
		goto emulate;
	}

	if (fpexc & FPEXC_EX) {
#ifndef CONFIG_CPU_FEROCEON
		/*
		 * Asynchronous exception. The instruction is read from FPINST
		 * and the interrupted instruction has to be restarted.
		 */
		trigger = fmrx(FPINST);
		regs->ARM_pc -= 4;
#endif
	} else if (!(fpexc & FPEXC_DEX)) {
		/*
		 * Illegal combination of bits. It can be caused by an
		 * unallocated VFP instruction but with FPSCR.IXE set and not
		 * on VFP subarch 1.
		 */
		 vfp_raise_exceptions(VFP_EXCEPTION_ERROR, trigger, fpscr, regs);
		goto exit;
	}

	/*
	 * Modify fpscr to indicate the number of iterations remaining.
	 * If FPEXC.EX is 0, FPEXC.DEX is 1 and the FPEXC.VV bit indicates
	 * whether FPEXC.VECITR or FPSCR.LEN is used.
	 */
	if (fpexc & (FPEXC_EX | FPEXC_VV)) {
		u32 len;

		len = fpexc + (1 << FPEXC_LENGTH_BIT);

		fpscr &= ~FPSCR_LENGTH_MASK;
		fpscr |= (len & FPEXC_LENGTH_MASK) << (FPSCR_LENGTH_BIT - FPEXC_LENGTH_BIT);
	}

	/*
	 * Handle the first FP instruction.  We used to take note of the
	 * FPEXC bounce reason, but this appears to be unreliable.
	 * Emulate the bounced instruction instead.
	 */
	exceptions = vfp_emulate_instruction(trigger, fpscr, regs);
	if (exceptions)
		vfp_raise_exceptions(exceptions, trigger, orig_fpscr, regs);

	/*
	 * If there isn't a second FP instruction, exit now. Note that
	 * the FPEXC.FP2V bit is valid only if FPEXC.EX is 1.
	 */
	if ((fpexc & (FPEXC_EX | FPEXC_FP2V)) != (FPEXC_EX | FPEXC_FP2V))
		goto exit;

	/*
	 * The barrier() here prevents fpinst2 being read
	 * before the condition above.
	 */
	barrier();
	trigger = fmrx(FPINST2);

 emulate:
	exceptions = vfp_emulate_instruction(trigger, orig_fpscr, regs);
	if (exceptions)
		vfp_raise_exceptions(exceptions, trigger, orig_fpscr, regs);
 exit:
	preempt_enable();
}