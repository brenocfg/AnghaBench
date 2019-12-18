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
struct fman_bmi_regs {int /*<<< orphan*/  fmbm_cfg1; } ;

/* Variables and functions */
 int BMI_CFG1_FIFO_SIZE_SHIFT ; 
 int FMAN_BMI_FIFO_UNITS ; 
 int ioread32be (int /*<<< orphan*/ *) ; 

uint32_t fman_get_total_fifo_size(struct fman_bmi_regs *bmi_rg)
{
	uint32_t reg, res;

	reg = ioread32be(&bmi_rg->fmbm_cfg1);
	res = (reg >> BMI_CFG1_FIFO_SIZE_SHIFT) & 0x3ff;
	return res * FMAN_BMI_FIFO_UNITS;
}