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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int CR4_XSAVE ; 
 scalar_t__ IS_BSP () ; 
 int /*<<< orphan*/  XCR0 ; 
 int /*<<< orphan*/  __INITIAL_FPUCW__ ; 
 int /*<<< orphan*/  __INITIAL_MXCSR__ ; 
 int /*<<< orphan*/  fldcw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fninit () ; 
 int /*<<< orphan*/  fpuinit_bsp1 () ; 
 int /*<<< orphan*/  fpuinit_bsp2 () ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldmxcsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_cr4 (int) ; 
 int /*<<< orphan*/  load_xcr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rcr4 () ; 
 int /*<<< orphan*/  start_emulating () ; 
 int /*<<< orphan*/  stop_emulating () ; 
 scalar_t__ use_xsave ; 
 int /*<<< orphan*/  xsave_mask ; 

void
fpuinit(void)
{
	register_t saveintr;
	u_int mxcsr;
	u_short control;

	if (IS_BSP())
		fpuinit_bsp1();

	if (use_xsave) {
		load_cr4(rcr4() | CR4_XSAVE);
		load_xcr(XCR0, xsave_mask);
	}

	/*
	 * XCR0 shall be set up before CPU can report the save area size.
	 */
	if (IS_BSP())
		fpuinit_bsp2();

	/*
	 * It is too early for critical_enter() to work on AP.
	 */
	saveintr = intr_disable();
	stop_emulating();
	fninit();
	control = __INITIAL_FPUCW__;
	fldcw(control);
	mxcsr = __INITIAL_MXCSR__;
	ldmxcsr(mxcsr);
	start_emulating();
	intr_restore(saveintr);
}