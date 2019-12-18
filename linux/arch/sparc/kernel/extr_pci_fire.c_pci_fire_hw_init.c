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
typedef  int u64 ;
struct pci_pbm_info {scalar_t__ pbm_regs; scalar_t__ controller_regs; } ;

/* Variables and functions */
 scalar_t__ FIRE_CORE_INTR_ENABLE ; 
 scalar_t__ FIRE_DMC_DBG_SEL_A ; 
 scalar_t__ FIRE_DMC_DBG_SEL_B ; 
 scalar_t__ FIRE_DMC_IENAB ; 
 int FIRE_FATAL_RESET_APE ; 
 int FIRE_FATAL_RESET_CPE ; 
 scalar_t__ FIRE_FATAL_RESET_CTL ; 
 int FIRE_FATAL_RESET_JI ; 
 int FIRE_FATAL_RESET_JR ; 
 int FIRE_FATAL_RESET_JW ; 
 int FIRE_FATAL_RESET_MB ; 
 int FIRE_FATAL_RESET_PIO ; 
 int FIRE_FATAL_RESET_SPARE ; 
 scalar_t__ FIRE_LPU_FCTRL_UCTRL ; 
 int FIRE_LPU_FCTRL_UCTRL_N ; 
 int FIRE_LPU_FCTRL_UCTRL_P ; 
 scalar_t__ FIRE_LPU_LLCFG ; 
 int FIRE_LPU_LLCFG_VC0 ; 
 scalar_t__ FIRE_LPU_LTSSM_CFG2 ; 
 scalar_t__ FIRE_LPU_LTSSM_CFG3 ; 
 scalar_t__ FIRE_LPU_LTSSM_CFG4 ; 
 scalar_t__ FIRE_LPU_LTSSM_CFG5 ; 
 scalar_t__ FIRE_LPU_RESET ; 
 scalar_t__ FIRE_LPU_TXL_FIFOP ; 
 scalar_t__ FIRE_PARITY_CONTROL ; 
 int FIRE_PARITY_ENAB ; 
 scalar_t__ FIRE_PEC_IENAB ; 
 scalar_t__ FIRE_TLU_CTRL ; 
 int FIRE_TLU_CTRL_CFG ; 
 int FIRE_TLU_CTRL_QDET ; 
 int FIRE_TLU_CTRL_TIM ; 
 scalar_t__ FIRE_TLU_DEV_CTRL ; 
 scalar_t__ FIRE_TLU_LINK_CTRL ; 
 int FIRE_TLU_LINK_CTRL_CLK ; 
 int upa_readq (scalar_t__) ; 
 int /*<<< orphan*/  upa_writeq (int,scalar_t__) ; 

__attribute__((used)) static void pci_fire_hw_init(struct pci_pbm_info *pbm)
{
	u64 val;

	upa_writeq(FIRE_PARITY_ENAB,
		   pbm->controller_regs + FIRE_PARITY_CONTROL);

	upa_writeq((FIRE_FATAL_RESET_SPARE |
		    FIRE_FATAL_RESET_MB |
		    FIRE_FATAL_RESET_CPE |
		    FIRE_FATAL_RESET_APE |
		    FIRE_FATAL_RESET_PIO |
		    FIRE_FATAL_RESET_JW |
		    FIRE_FATAL_RESET_JI |
		    FIRE_FATAL_RESET_JR),
		   pbm->controller_regs + FIRE_FATAL_RESET_CTL);

	upa_writeq(~(u64)0, pbm->controller_regs + FIRE_CORE_INTR_ENABLE);

	val = upa_readq(pbm->pbm_regs + FIRE_TLU_CTRL);
	val |= (FIRE_TLU_CTRL_TIM |
		FIRE_TLU_CTRL_QDET |
		FIRE_TLU_CTRL_CFG);
	upa_writeq(val, pbm->pbm_regs + FIRE_TLU_CTRL);
	upa_writeq(0, pbm->pbm_regs + FIRE_TLU_DEV_CTRL);
	upa_writeq(FIRE_TLU_LINK_CTRL_CLK,
		   pbm->pbm_regs + FIRE_TLU_LINK_CTRL);

	upa_writeq(0, pbm->pbm_regs + FIRE_LPU_RESET);
	upa_writeq(FIRE_LPU_LLCFG_VC0, pbm->pbm_regs + FIRE_LPU_LLCFG);
	upa_writeq((FIRE_LPU_FCTRL_UCTRL_N | FIRE_LPU_FCTRL_UCTRL_P),
		   pbm->pbm_regs + FIRE_LPU_FCTRL_UCTRL);
	upa_writeq(((0xffff << 16) | (0x0000 << 0)),
		   pbm->pbm_regs + FIRE_LPU_TXL_FIFOP);
	upa_writeq(3000000, pbm->pbm_regs + FIRE_LPU_LTSSM_CFG2);
	upa_writeq(500000, pbm->pbm_regs + FIRE_LPU_LTSSM_CFG3);
	upa_writeq((2 << 16) | (140 << 8),
		   pbm->pbm_regs + FIRE_LPU_LTSSM_CFG4);
	upa_writeq(0, pbm->pbm_regs + FIRE_LPU_LTSSM_CFG5);

	upa_writeq(~(u64)0, pbm->pbm_regs + FIRE_DMC_IENAB);
	upa_writeq(0, pbm->pbm_regs + FIRE_DMC_DBG_SEL_A);
	upa_writeq(0, pbm->pbm_regs + FIRE_DMC_DBG_SEL_B);

	upa_writeq(~(u64)0, pbm->pbm_regs + FIRE_PEC_IENAB);
}