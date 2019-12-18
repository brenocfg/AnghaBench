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
struct fman_fpm_regs {int /*<<< orphan*/  fmfp_prc; } ;

/* Variables and functions */
 int FPM_PORT_FM_CTL_PORTID_SHIFT ; 
 int FPM_PRC_ORA_FM_CTL_SEL_SHIFT ; 
 int FPM_PRT_FM_CTL1 ; 
 int FPM_PRT_FM_CTL2 ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_order_restoration_per_port(struct fman_fpm_regs *fpm_rg,
					uint8_t port_id,
					bool independent_mode,
					bool is_rx_port)
{
	uint32_t tmp = 0;

	tmp = (uint32_t)(port_id << FPM_PORT_FM_CTL_PORTID_SHIFT);
	if (independent_mode) {
		if (is_rx_port)
			tmp |= (FPM_PRT_FM_CTL1 <<
				FPM_PRC_ORA_FM_CTL_SEL_SHIFT) | FPM_PRT_FM_CTL1;
		else
			tmp |= (FPM_PRT_FM_CTL2 <<
				FPM_PRC_ORA_FM_CTL_SEL_SHIFT) | FPM_PRT_FM_CTL2;
	} else {
		tmp |= (FPM_PRT_FM_CTL2|FPM_PRT_FM_CTL1);

		/* order restoration */
		if (port_id % 2)
			tmp |= (FPM_PRT_FM_CTL1 <<
					FPM_PRC_ORA_FM_CTL_SEL_SHIFT);
		else
			tmp |= (FPM_PRT_FM_CTL2 <<
					FPM_PRC_ORA_FM_CTL_SEL_SHIFT);
	}
	iowrite32be(tmp, &fpm_rg->fmfp_prc);
}