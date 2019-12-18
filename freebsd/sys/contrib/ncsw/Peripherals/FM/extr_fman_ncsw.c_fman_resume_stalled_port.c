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
typedef  scalar_t__ uint32_t ;
struct fman_fpm_regs {int /*<<< orphan*/  fmfp_prc; } ;

/* Variables and functions */
 int FPM_PORT_FM_CTL_PORTID_SHIFT ; 
 int FPM_PRC_REALSE_STALLED ; 
 int /*<<< orphan*/  iowrite32be (scalar_t__,int /*<<< orphan*/ *) ; 

void fman_resume_stalled_port(struct fman_fpm_regs *fpm_rg, uint8_t port_id)
{
	uint32_t	tmp;

	tmp = (uint32_t)((port_id << FPM_PORT_FM_CTL_PORTID_SHIFT) |
				FPM_PRC_REALSE_STALLED);
	iowrite32be(tmp, &fpm_rg->fmfp_prc);
}