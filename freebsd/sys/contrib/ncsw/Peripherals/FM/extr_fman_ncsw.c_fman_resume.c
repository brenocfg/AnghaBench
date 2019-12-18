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
struct fman_fpm_regs {int /*<<< orphan*/  fmfp_ee; } ;

/* Variables and functions */
 int FPM_EV_MASK_DOUBLE_ECC ; 
 int FPM_EV_MASK_RELEASE_FM ; 
 int FPM_EV_MASK_SINGLE_ECC ; 
 int FPM_EV_MASK_STALL ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_resume(struct fman_fpm_regs *fpm_rg)
{
	uint32_t tmp;

	tmp = ioread32be(&fpm_rg->fmfp_ee);
	/* clear tmp_reg event bits in order not to clear standing events */
	tmp &= ~(FPM_EV_MASK_DOUBLE_ECC |
			FPM_EV_MASK_STALL |
			FPM_EV_MASK_SINGLE_ECC);
	tmp |= FPM_EV_MASK_RELEASE_FM;

	iowrite32be(tmp, &fpm_rg->fmfp_ee);
}