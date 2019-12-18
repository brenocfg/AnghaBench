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
typedef  void* u64 ;
typedef  scalar_t__ u32 ;
struct pt_regs {void* ccr; void* msr; void* nip; void* dsisr; void* dar; void* xer; void* link; void* ctr; void** gpr; } ;

/* Variables and functions */
#define  HDAT_FADUMP_REG_ID_CCR 135 
#define  HDAT_FADUMP_REG_ID_MSR 134 
#define  HDAT_FADUMP_REG_ID_NIP 133 
 scalar_t__ HDAT_FADUMP_REG_TYPE_GPR ; 
#define  SPRN_CTR 132 
#define  SPRN_DAR 131 
#define  SPRN_DSISR 130 
#define  SPRN_LR 129 
#define  SPRN_XER 128 

__attribute__((used)) static inline void opal_fadump_set_regval_regnum(struct pt_regs *regs,
						 u32 reg_type, u32 reg_num,
						 u64 reg_val)
{
	if (reg_type == HDAT_FADUMP_REG_TYPE_GPR) {
		if (reg_num < 32)
			regs->gpr[reg_num] = reg_val;
		return;
	}

	switch (reg_num) {
	case SPRN_CTR:
		regs->ctr = reg_val;
		break;
	case SPRN_LR:
		regs->link = reg_val;
		break;
	case SPRN_XER:
		regs->xer = reg_val;
		break;
	case SPRN_DAR:
		regs->dar = reg_val;
		break;
	case SPRN_DSISR:
		regs->dsisr = reg_val;
		break;
	case HDAT_FADUMP_REG_ID_NIP:
		regs->nip = reg_val;
		break;
	case HDAT_FADUMP_REG_ID_MSR:
		regs->msr = reg_val;
		break;
	case HDAT_FADUMP_REG_ID_CCR:
		regs->ccr = reg_val;
		break;
	}
}