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
typedef  int /*<<< orphan*/  uint16_t ;
struct fman_bmi_regs {int /*<<< orphan*/ * fmbm_pfs; } ;

/* Variables and functions */
 int BMI_FIFO_SIZE_MASK ; 
 int ioread32be (int /*<<< orphan*/ *) ; 

uint16_t fman_get_size_of_fifo(struct fman_bmi_regs *bmi_rg, uint8_t port_id)
{
	uint32_t tmp_reg;

    if ((port_id > 63) || (port_id < 1))
            return 0;

	tmp_reg = ioread32be(&bmi_rg->fmbm_pfs[port_id - 1]);
	return (uint16_t)((tmp_reg & BMI_FIFO_SIZE_MASK) + 1);
}