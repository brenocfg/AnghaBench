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
struct fman_bmi_regs {int /*<<< orphan*/ * fmbm_pp; } ;

/* Variables and functions */
 int BMI_EXTRA_NUM_OF_DMAS_SHIFT ; 
 int BMI_NUM_OF_EXTRA_DMAS_MASK ; 
 int ioread32be (int /*<<< orphan*/ *) ; 

uint8_t fman_get_num_extra_dmas(struct fman_bmi_regs *bmi_rg, uint8_t port_id)
{
	uint32_t tmp;

	if ((port_id > 63) || (port_id < 1))
	        return 0;

	tmp = ioread32be(&bmi_rg->fmbm_pp[port_id - 1]);
	return (uint8_t)((tmp & BMI_NUM_OF_EXTRA_DMAS_MASK) >>
			BMI_EXTRA_NUM_OF_DMAS_SHIFT);
}