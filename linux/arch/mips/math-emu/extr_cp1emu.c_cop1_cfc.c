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
struct TYPE_2__ {int fpu_id; } ;

/* Variables and functions */
#define  FPCREG_CSR 132 
#define  FPCREG_FCCR 131 
#define  FPCREG_FENR 130 
#define  FPCREG_FEXR 129 
#define  FPCREG_RID 128 
 int FPU_CSR_ALL_E ; 
 int FPU_CSR_ALL_S ; 
 int FPU_CSR_ALL_X ; 
 int FPU_CSR_COND1_S ; 
 int FPU_CSR_COND_S ; 
 int FPU_CSR_FS_S ; 
 int FPU_CSR_RM ; 
 int MIPSInst_RD (int /*<<< orphan*/ ) ; 
 size_t MIPSInst_RT (int /*<<< orphan*/ ) ; 
 int MIPS_FCCR_COND0 ; 
 int MIPS_FCCR_COND0_S ; 
 int MIPS_FCCR_COND1_S ; 
 int MIPS_FCCR_CONDX ; 
 int MIPS_FENR_FS ; 
 int MIPS_FENR_FS_S ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  cpu_has_mips_r ; 
 int /*<<< orphan*/  pr_debug (char*,void*,size_t,int) ; 

__attribute__((used)) static inline void cop1_cfc(struct pt_regs *xcp, struct mips_fpu_struct *ctx,
			    mips_instruction ir)
{
	u32 fcr31 = ctx->fcr31;
	u32 value = 0;

	switch (MIPSInst_RD(ir)) {
	case FPCREG_CSR:
		value = fcr31;
		pr_debug("%p gpr[%d]<-csr=%08x\n",
			 (void *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		break;

	case FPCREG_FENR:
		if (!cpu_has_mips_r)
			break;
		value = (fcr31 >> (FPU_CSR_FS_S - MIPS_FENR_FS_S)) &
			MIPS_FENR_FS;
		value |= fcr31 & (FPU_CSR_ALL_E | FPU_CSR_RM);
		pr_debug("%p gpr[%d]<-enr=%08x\n",
			 (void *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		break;

	case FPCREG_FEXR:
		if (!cpu_has_mips_r)
			break;
		value = fcr31 & (FPU_CSR_ALL_X | FPU_CSR_ALL_S);
		pr_debug("%p gpr[%d]<-exr=%08x\n",
			 (void *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		break;

	case FPCREG_FCCR:
		if (!cpu_has_mips_r)
			break;
		value = (fcr31 >> (FPU_CSR_COND_S - MIPS_FCCR_COND0_S)) &
			MIPS_FCCR_COND0;
		value |= (fcr31 >> (FPU_CSR_COND1_S - MIPS_FCCR_COND1_S)) &
			 (MIPS_FCCR_CONDX & ~MIPS_FCCR_COND0);
		pr_debug("%p gpr[%d]<-ccr=%08x\n",
			 (void *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		break;

	case FPCREG_RID:
		value = boot_cpu_data.fpu_id;
		break;

	default:
		break;
	}

	if (MIPSInst_RT(ir))
		xcp->regs[MIPSInst_RT(ir)] = value;
}