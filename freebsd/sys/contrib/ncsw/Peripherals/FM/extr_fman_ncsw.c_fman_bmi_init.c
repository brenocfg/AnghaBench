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
struct fman_cfg {int fifo_base_addr; int total_fifo_size; int total_num_of_tasks; int exceptions; } ;
struct fman_bmi_regs {int /*<<< orphan*/  fmbm_ier; int /*<<< orphan*/  fmbm_ievr; int /*<<< orphan*/  fmbm_cfg2; int /*<<< orphan*/  fmbm_cfg1; } ;

/* Variables and functions */
 int BMI_CFG1_FIFO_SIZE_SHIFT ; 
 int BMI_CFG2_TASKS_SHIFT ; 
 int BMI_ERR_INTR_EN_DISPATCH_RAM_ECC ; 
 int BMI_ERR_INTR_EN_LIST_RAM_ECC ; 
 int BMI_ERR_INTR_EN_STATISTICS_RAM_ECC ; 
 int BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC ; 
 int BMI_FIFO_ALIGN ; 
 int FMAN_BMI_FIFO_UNITS ; 
 int FMAN_EX_BMI_DISPATCH_RAM_ECC ; 
 int FMAN_EX_BMI_LIST_RAM_ECC ; 
 int FMAN_EX_BMI_PIPELINE_ECC ; 
 int FMAN_EX_BMI_STATISTICS_RAM_ECC ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_bmi_init(struct fman_bmi_regs *bmi_rg, struct fman_cfg *cfg)
{
	uint32_t tmp_reg;

	/**********************/
	/* Init BMI Registers */
	/**********************/

	/* define common resources */
	tmp_reg = cfg->fifo_base_addr;
	tmp_reg = tmp_reg / BMI_FIFO_ALIGN;

	tmp_reg |= ((cfg->total_fifo_size / FMAN_BMI_FIFO_UNITS - 1) <<
			BMI_CFG1_FIFO_SIZE_SHIFT);
	iowrite32be(tmp_reg, &bmi_rg->fmbm_cfg1);

	tmp_reg = ((uint32_t)(cfg->total_num_of_tasks - 1) <<
			BMI_CFG2_TASKS_SHIFT);
	/* num of DMA's will be dynamically updated when each port is set */
	iowrite32be(tmp_reg, &bmi_rg->fmbm_cfg2);

	/* define unmaskable exceptions, enable and clear events */
	tmp_reg = 0;
	iowrite32be(BMI_ERR_INTR_EN_LIST_RAM_ECC |
			BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC |
			BMI_ERR_INTR_EN_STATISTICS_RAM_ECC |
			BMI_ERR_INTR_EN_DISPATCH_RAM_ECC,
			&bmi_rg->fmbm_ievr);

	if (cfg->exceptions & FMAN_EX_BMI_LIST_RAM_ECC)
		tmp_reg |= BMI_ERR_INTR_EN_LIST_RAM_ECC;
	if (cfg->exceptions & FMAN_EX_BMI_PIPELINE_ECC)
		tmp_reg |= BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC;
	if (cfg->exceptions & FMAN_EX_BMI_STATISTICS_RAM_ECC)
		tmp_reg |= BMI_ERR_INTR_EN_STATISTICS_RAM_ECC;
	if (cfg->exceptions & FMAN_EX_BMI_DISPATCH_RAM_ECC)
		tmp_reg |= BMI_ERR_INTR_EN_DISPATCH_RAM_ECC;
	iowrite32be(tmp_reg, &bmi_rg->fmbm_ier);

	return 0;
}