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
typedef  int uint32_t ;
struct fman_fpm_regs {int /*<<< orphan*/  fm_rie; int /*<<< orphan*/  fm_rcr; int /*<<< orphan*/ * fmfp_cev; int /*<<< orphan*/  fmfp_ee; int /*<<< orphan*/  fmfp_dist2; int /*<<< orphan*/  fmfp_dist1; int /*<<< orphan*/  fmfp_mxd; } ;
struct fman_cfg {int disp_limit_tsh; int exceptions; int catastrophic_err; int dma_err; int num_of_fman_ctrl_evnt_regs; scalar_t__ en_iram_test_mode; scalar_t__ en_muram_test_mode; scalar_t__ external_ecc_rams_enable; int /*<<< orphan*/  halt_on_unrecov_ecc_err; int /*<<< orphan*/  halt_on_external_activ; scalar_t__ fm_ctl2_disp_tsh; scalar_t__ fm_ctl1_disp_tsh; scalar_t__ qmi_deq_disp_tsh; scalar_t__ qmi_enq_disp_tsh; scalar_t__ bmi_disp_tsh; scalar_t__ plcr_disp_tsh; scalar_t__ kg_disp_tsh; scalar_t__ prs_disp_tsh; } ;

/* Variables and functions */
 int FMAN_EX_FPM_DOUBLE_ECC ; 
 int FMAN_EX_FPM_SINGLE_ECC ; 
 int FMAN_EX_FPM_STALL_ON_TASKS ; 
 int FMAN_EX_IRAM_ECC ; 
 int FMAN_EX_NURAM_ECC ; 
 int FPM_DISP_LIMIT_SHIFT ; 
 int FPM_EV_MASK_CAT_ERR_SHIFT ; 
 int FPM_EV_MASK_DMA_ERR_SHIFT ; 
 int FPM_EV_MASK_DOUBLE_ECC ; 
 int FPM_EV_MASK_DOUBLE_ECC_EN ; 
 int FPM_EV_MASK_ECC_ERR_HALT ; 
 int FPM_EV_MASK_EXTERNAL_HALT ; 
 int FPM_EV_MASK_SINGLE_ECC ; 
 int FPM_EV_MASK_SINGLE_ECC_EN ; 
 int FPM_EV_MASK_STALL ; 
 int FPM_EV_MASK_STALL_EN ; 
 int FPM_IRAM_ECC_ERR_EX_EN ; 
 int FPM_MURAM_ECC_ERR_EX_EN ; 
 int FPM_RAM_IRAM_ECC ; 
 int FPM_RAM_IRAM_TEST_ECC ; 
 int FPM_RAM_MURAM_ECC ; 
 int FPM_RAM_MURAM_TEST_ECC ; 
 int FPM_RAM_RAMS_ECC_EN_SRC_SEL ; 
 int FPM_THR1_BMI_SHIFT ; 
 int FPM_THR1_KG_SHIFT ; 
 int FPM_THR1_PLCR_SHIFT ; 
 int FPM_THR1_PRS_SHIFT ; 
 int FPM_THR2_FM_CTL1_SHIFT ; 
 int FPM_THR2_FM_CTL2_SHIFT ; 
 int FPM_THR2_QMI_DEQ_SHIFT ; 
 int FPM_THR2_QMI_ENQ_SHIFT ; 
 int /*<<< orphan*/  fman_enable_rams_ecc (struct fman_fpm_regs*) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_fpm_init(struct fman_fpm_regs *fpm_rg, struct fman_cfg *cfg)
{
	uint32_t tmp_reg;
	int i;

	/**********************/
	/* Init FPM Registers */
	/**********************/
	tmp_reg = (uint32_t)(cfg->disp_limit_tsh << FPM_DISP_LIMIT_SHIFT);
	iowrite32be(tmp_reg, &fpm_rg->fmfp_mxd);

	tmp_reg = (((uint32_t)cfg->prs_disp_tsh << FPM_THR1_PRS_SHIFT) |
		((uint32_t)cfg->kg_disp_tsh << FPM_THR1_KG_SHIFT) |
		((uint32_t)cfg->plcr_disp_tsh << FPM_THR1_PLCR_SHIFT) |
		((uint32_t)cfg->bmi_disp_tsh << FPM_THR1_BMI_SHIFT));
	iowrite32be(tmp_reg, &fpm_rg->fmfp_dist1);

	tmp_reg = (((uint32_t)cfg->qmi_enq_disp_tsh << FPM_THR2_QMI_ENQ_SHIFT) |
		((uint32_t)cfg->qmi_deq_disp_tsh << FPM_THR2_QMI_DEQ_SHIFT) |
		((uint32_t)cfg->fm_ctl1_disp_tsh << FPM_THR2_FM_CTL1_SHIFT) |
		((uint32_t)cfg->fm_ctl2_disp_tsh << FPM_THR2_FM_CTL2_SHIFT));
	iowrite32be(tmp_reg, &fpm_rg->fmfp_dist2);

	/* define exceptions and error behavior */
	tmp_reg = 0;
	/* Clear events */
	tmp_reg |= (FPM_EV_MASK_STALL | FPM_EV_MASK_DOUBLE_ECC |
		FPM_EV_MASK_SINGLE_ECC);
	/* enable interrupts */
	if (cfg->exceptions & FMAN_EX_FPM_STALL_ON_TASKS)
		tmp_reg |= FPM_EV_MASK_STALL_EN;
	if (cfg->exceptions & FMAN_EX_FPM_SINGLE_ECC)
		tmp_reg |= FPM_EV_MASK_SINGLE_ECC_EN;
	if (cfg->exceptions & FMAN_EX_FPM_DOUBLE_ECC)
		tmp_reg |= FPM_EV_MASK_DOUBLE_ECC_EN;
	tmp_reg |= (cfg->catastrophic_err  << FPM_EV_MASK_CAT_ERR_SHIFT);
	tmp_reg |= (cfg->dma_err << FPM_EV_MASK_DMA_ERR_SHIFT);
	if (!cfg->halt_on_external_activ)
		tmp_reg |= FPM_EV_MASK_EXTERNAL_HALT;
	if (!cfg->halt_on_unrecov_ecc_err)
		tmp_reg |= FPM_EV_MASK_ECC_ERR_HALT;
	iowrite32be(tmp_reg, &fpm_rg->fmfp_ee);

	/* clear all fmCtls event registers */
	for (i = 0; i < cfg->num_of_fman_ctrl_evnt_regs; i++)
		iowrite32be(0xFFFFFFFF, &fpm_rg->fmfp_cev[i]);

	/* RAM ECC -  enable and clear events*/
	/* first we need to clear all parser memory,
	 * as it is uninitialized and may cause ECC errors */
	/* event bits */
	tmp_reg = (FPM_RAM_MURAM_ECC | FPM_RAM_IRAM_ECC);
	/* Rams enable not effected by RCR bit, but by a COP configuration */
	if (cfg->external_ecc_rams_enable)
		tmp_reg |= FPM_RAM_RAMS_ECC_EN_SRC_SEL;

	/* enable test mode */
	if (cfg->en_muram_test_mode)
		tmp_reg |= FPM_RAM_MURAM_TEST_ECC;
	if (cfg->en_iram_test_mode)
		tmp_reg |= FPM_RAM_IRAM_TEST_ECC;
	iowrite32be(tmp_reg, &fpm_rg->fm_rcr);

	tmp_reg = 0;
	if (cfg->exceptions & FMAN_EX_IRAM_ECC) {
		tmp_reg |= FPM_IRAM_ECC_ERR_EX_EN;
		fman_enable_rams_ecc(fpm_rg);
	}
	if (cfg->exceptions & FMAN_EX_NURAM_ECC) {
		tmp_reg |= FPM_MURAM_ECC_ERR_EX_EN;
		fman_enable_rams_ecc(fpm_rg);
	}
	iowrite32be(tmp_reg, &fpm_rg->fm_rie);

	return 0;
}