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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESR_ELx_SYS64_ISS_RT (unsigned int) ; 
 int /*<<< orphan*/  ILL_ILLOPC ; 
 int /*<<< orphan*/  SIGILL ; 
 scalar_t__ do_emulate_mrs (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esr_sys64_to_sysreg (unsigned int) ; 
 int /*<<< orphan*/  force_signal_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mrs_handler(unsigned int esr, struct pt_regs *regs)
{
	u32 sysreg, rt;

	rt = ESR_ELx_SYS64_ISS_RT(esr);
	sysreg = esr_sys64_to_sysreg(esr);

	if (do_emulate_mrs(regs, sysreg, rt) != 0)
		force_signal_inject(SIGILL, ILL_ILLOPC, regs->pc);
}