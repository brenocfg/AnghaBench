#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pt_regs {int* regs; scalar_t__ cp0_epc; } ;
struct mips_fpu_struct {int fcr31; } ;
typedef  int /*<<< orphan*/  mips_instruction ;
struct TYPE_2__ {int fpu_msk31; } ;

/* Variables and functions */
#define  FPCREG_CSR 131 
#define  FPCREG_FCCR 130 
#define  FPCREG_FENR 129 
#define  FPCREG_FEXR 128 
 int FPU_CSR_ALL_E ; 
 int FPU_CSR_ALL_S ; 
 int FPU_CSR_ALL_X ; 
 int FPU_CSR_COND ; 
 int FPU_CSR_COND1_S ; 
 int FPU_CSR_CONDX ; 
 int FPU_CSR_COND_S ; 
 int FPU_CSR_FS ; 
 int FPU_CSR_FS_S ; 
 int FPU_CSR_RM ; 
 int MIPSInst_RD (int /*<<< orphan*/ ) ; 
 size_t MIPSInst_RT (int /*<<< orphan*/ ) ; 
 int MIPS_FCCR_COND0_S ; 
 int MIPS_FCCR_COND1_S ; 
 int MIPS_FENR_FS_S ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  cpu_has_mips_r ; 
 int /*<<< orphan*/  pr_debug (char*,void*,size_t,int) ; 

__attribute__((used)) static inline void cop1_ctc(struct pt_regs *xcp, struct mips_fpu_struct *ctx,
			    mips_instruction ir)
{
	u32 fcr31 = ctx->fcr31;
	u32 value;
	u32 mask;

	if (MIPSInst_RT(ir) == 0)
		value = 0;
	else
		value = xcp->regs[MIPSInst_RT(ir)];

	switch (MIPSInst_RD(ir)) {
	case FPCREG_CSR:
		pr_debug("%p gpr[%d]->csr=%08x\n",
			 (void *)xcp->cp0_epc, MIPSInst_RT(ir), value);

		/* Preserve read-only bits.  */
		mask = boot_cpu_data.fpu_msk31;
		fcr31 = (value & ~mask) | (fcr31 & mask);
		break;

	case FPCREG_FENR:
		if (!cpu_has_mips_r)
			break;
		pr_debug("%p gpr[%d]->enr=%08x\n",
			 (void *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		fcr31 &= ~(FPU_CSR_FS | FPU_CSR_ALL_E | FPU_CSR_RM);
		fcr31 |= (value << (FPU_CSR_FS_S - MIPS_FENR_FS_S)) &
			 FPU_CSR_FS;
		fcr31 |= value & (FPU_CSR_ALL_E | FPU_CSR_RM);
		break;

	case FPCREG_FEXR:
		if (!cpu_has_mips_r)
			break;
		pr_debug("%p gpr[%d]->exr=%08x\n",
			 (void *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		fcr31 &= ~(FPU_CSR_ALL_X | FPU_CSR_ALL_S);
		fcr31 |= value & (FPU_CSR_ALL_X | FPU_CSR_ALL_S);
		break;

	case FPCREG_FCCR:
		if (!cpu_has_mips_r)
			break;
		pr_debug("%p gpr[%d]->ccr=%08x\n",
			 (void *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		fcr31 &= ~(FPU_CSR_CONDX | FPU_CSR_COND);
		fcr31 |= (value << (FPU_CSR_COND_S - MIPS_FCCR_COND0_S)) &
			 FPU_CSR_COND;
		fcr31 |= (value << (FPU_CSR_COND1_S - MIPS_FCCR_COND1_S)) &
			 FPU_CSR_CONDX;
		break;

	default:
		break;
	}

	ctx->fcr31 = fcr31;
}