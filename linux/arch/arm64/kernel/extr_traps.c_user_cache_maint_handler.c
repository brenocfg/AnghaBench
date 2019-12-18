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
struct pt_regs {int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_INSN_SIZE ; 
#define  ESR_ELx_SYS64_ISS_CRM_DC_CIVAC 133 
#define  ESR_ELx_SYS64_ISS_CRM_DC_CVAC 132 
#define  ESR_ELx_SYS64_ISS_CRM_DC_CVADP 131 
#define  ESR_ELx_SYS64_ISS_CRM_DC_CVAP 130 
#define  ESR_ELx_SYS64_ISS_CRM_DC_CVAU 129 
#define  ESR_ELx_SYS64_ISS_CRM_IC_IVAU 128 
 unsigned int ESR_ELx_SYS64_ISS_CRM_MASK ; 
 unsigned int ESR_ELx_SYS64_ISS_CRM_SHIFT ; 
 int ESR_ELx_SYS64_ISS_RT (unsigned int) ; 
 int /*<<< orphan*/  ILL_ILLOPC ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  __user_cache_maint (char*,unsigned long,int) ; 
 int /*<<< orphan*/  arm64_notify_segfault (unsigned long) ; 
 int /*<<< orphan*/  arm64_skip_faulting_instruction (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_signal_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_regs_read_reg (struct pt_regs*,int) ; 
 unsigned long untagged_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void user_cache_maint_handler(unsigned int esr, struct pt_regs *regs)
{
	unsigned long address;
	int rt = ESR_ELx_SYS64_ISS_RT(esr);
	int crm = (esr & ESR_ELx_SYS64_ISS_CRM_MASK) >> ESR_ELx_SYS64_ISS_CRM_SHIFT;
	int ret = 0;

	address = untagged_addr(pt_regs_read_reg(regs, rt));

	switch (crm) {
	case ESR_ELx_SYS64_ISS_CRM_DC_CVAU:	/* DC CVAU, gets promoted */
		__user_cache_maint("dc civac", address, ret);
		break;
	case ESR_ELx_SYS64_ISS_CRM_DC_CVAC:	/* DC CVAC, gets promoted */
		__user_cache_maint("dc civac", address, ret);
		break;
	case ESR_ELx_SYS64_ISS_CRM_DC_CVADP:	/* DC CVADP */
		__user_cache_maint("sys 3, c7, c13, 1", address, ret);
		break;
	case ESR_ELx_SYS64_ISS_CRM_DC_CVAP:	/* DC CVAP */
		__user_cache_maint("sys 3, c7, c12, 1", address, ret);
		break;
	case ESR_ELx_SYS64_ISS_CRM_DC_CIVAC:	/* DC CIVAC */
		__user_cache_maint("dc civac", address, ret);
		break;
	case ESR_ELx_SYS64_ISS_CRM_IC_IVAU:	/* IC IVAU */
		__user_cache_maint("ic ivau", address, ret);
		break;
	default:
		force_signal_inject(SIGILL, ILL_ILLOPC, regs->pc);
		return;
	}

	if (ret)
		arm64_notify_segfault(address);
	else
		arm64_skip_faulting_instruction(regs, AARCH64_INSN_SIZE);
}