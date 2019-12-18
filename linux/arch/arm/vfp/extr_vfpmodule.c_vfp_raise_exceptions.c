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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int FPE_FLTDIV ; 
 int FPE_FLTINV ; 
 int FPE_FLTOVF ; 
 int FPE_FLTRES ; 
 int FPE_FLTUND ; 
 int /*<<< orphan*/  FPSCR ; 
 int FPSCR_C ; 
 int /*<<< orphan*/  FPSCR_DZC ; 
 int /*<<< orphan*/  FPSCR_DZE ; 
 int /*<<< orphan*/  FPSCR_IOC ; 
 int /*<<< orphan*/  FPSCR_IOE ; 
 int /*<<< orphan*/  FPSCR_IXC ; 
 int /*<<< orphan*/  FPSCR_IXE ; 
 int FPSCR_N ; 
 int /*<<< orphan*/  FPSCR_OFC ; 
 int /*<<< orphan*/  FPSCR_OFE ; 
 int /*<<< orphan*/  FPSCR_UFC ; 
 int /*<<< orphan*/  FPSCR_UFE ; 
 int FPSCR_V ; 
 int FPSCR_Z ; 
 int /*<<< orphan*/  RAISE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int VFP_EXCEPTION_ERROR ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  vfp_panic (char*,int) ; 
 int /*<<< orphan*/  vfp_raise_sigfpe (int,struct pt_regs*) ; 

__attribute__((used)) static void vfp_raise_exceptions(u32 exceptions, u32 inst, u32 fpscr, struct pt_regs *regs)
{
	int si_code = 0;

	pr_debug("VFP: raising exceptions %08x\n", exceptions);

	if (exceptions == VFP_EXCEPTION_ERROR) {
		vfp_panic("unhandled bounce", inst);
		vfp_raise_sigfpe(FPE_FLTINV, regs);
		return;
	}

	/*
	 * If any of the status flags are set, update the FPSCR.
	 * Comparison instructions always return at least one of
	 * these flags set.
	 */
	if (exceptions & (FPSCR_N|FPSCR_Z|FPSCR_C|FPSCR_V))
		fpscr &= ~(FPSCR_N|FPSCR_Z|FPSCR_C|FPSCR_V);

	fpscr |= exceptions;

	fmxr(FPSCR, fpscr);

#define RAISE(stat,en,sig)				\
	if (exceptions & stat && fpscr & en)		\
		si_code = sig;

	/*
	 * These are arranged in priority order, least to highest.
	 */
	RAISE(FPSCR_DZC, FPSCR_DZE, FPE_FLTDIV);
	RAISE(FPSCR_IXC, FPSCR_IXE, FPE_FLTRES);
	RAISE(FPSCR_UFC, FPSCR_UFE, FPE_FLTUND);
	RAISE(FPSCR_OFC, FPSCR_OFE, FPE_FLTOVF);
	RAISE(FPSCR_IOC, FPSCR_IOE, FPE_FLTINV);

	if (si_code)
		vfp_raise_sigfpe(si_code, regs);
}