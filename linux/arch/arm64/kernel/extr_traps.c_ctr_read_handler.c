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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_INSN_SIZE ; 
 int ESR_ELx_SYS64_ISS_RT (unsigned int) ; 
 int /*<<< orphan*/  arm64_ftr_reg_ctrel0 ; 
 unsigned long arm64_ftr_reg_user_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm64_skip_faulting_instruction (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_regs_write_reg (struct pt_regs*,int,unsigned long) ; 

__attribute__((used)) static void ctr_read_handler(unsigned int esr, struct pt_regs *regs)
{
	int rt = ESR_ELx_SYS64_ISS_RT(esr);
	unsigned long val = arm64_ftr_reg_user_value(&arm64_ftr_reg_ctrel0);

	pt_regs_write_reg(regs, rt, val);

	arm64_skip_faulting_instruction(regs, AARCH64_INSN_SIZE);
}