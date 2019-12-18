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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fman_bmi_regs {int /*<<< orphan*/  fmbm_cfg2; int /*<<< orphan*/ * fmbm_pp; } ;

/* Variables and functions */
 int BMI_CFG2_DMAS_MASK ; 
 int BMI_CFG2_DMAS_SHIFT ; 
 int BMI_EXTRA_NUM_OF_DMAS_SHIFT ; 
 int BMI_NUM_OF_DMAS_MASK ; 
 int BMI_NUM_OF_DMAS_SHIFT ; 
 int BMI_NUM_OF_EXTRA_DMAS_MASK ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_num_of_open_dmas(struct fman_bmi_regs *bmi_rg,
				uint8_t port_id,
				uint8_t num_open_dmas,
				uint8_t num_extra_open_dmas,
				uint8_t total_num_dmas)
{
	uint32_t tmp = 0;

	if ((port_id > 63) || (port_id < 1))
	    return;

	/* calculate reg */
	tmp = ioread32be(&bmi_rg->fmbm_pp[port_id - 1]) &
			~(BMI_NUM_OF_DMAS_MASK | BMI_NUM_OF_EXTRA_DMAS_MASK);
	tmp |= (uint32_t)(((num_open_dmas-1) << BMI_NUM_OF_DMAS_SHIFT) |
			(num_extra_open_dmas << BMI_EXTRA_NUM_OF_DMAS_SHIFT));
	iowrite32be(tmp, &bmi_rg->fmbm_pp[port_id - 1]);

	/* update total num of DMA's with committed number of open DMAS,
	 * and max uncommitted pool. */
    if (total_num_dmas)
    {
        tmp = ioread32be(&bmi_rg->fmbm_cfg2) & ~BMI_CFG2_DMAS_MASK;
        tmp |= (uint32_t)(total_num_dmas - 1) << BMI_CFG2_DMAS_SHIFT;
        iowrite32be(tmp, &bmi_rg->fmbm_cfg2);
    }
}