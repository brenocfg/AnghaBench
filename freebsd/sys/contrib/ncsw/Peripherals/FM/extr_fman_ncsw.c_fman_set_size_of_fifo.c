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
struct fman_bmi_regs {int /*<<< orphan*/ * fmbm_pfs; } ;

/* Variables and functions */
 int BMI_EXTRA_FIFO_SIZE_SHIFT ; 
 int FMAN_BMI_FIFO_UNITS ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_size_of_fifo(struct fman_bmi_regs *bmi_rg,
				uint8_t port_id,
				uint32_t sz_fifo,
				uint32_t extra_sz_fifo)
{
	uint32_t tmp;

	if ((port_id > 63) || (port_id < 1))
	        return;

	/* calculate reg */
	tmp = (uint32_t)((sz_fifo / FMAN_BMI_FIFO_UNITS - 1) |
		((extra_sz_fifo / FMAN_BMI_FIFO_UNITS) <<
				BMI_EXTRA_FIFO_SIZE_SHIFT));
	iowrite32be(tmp, &bmi_rg->fmbm_pfs[port_id - 1]);
}