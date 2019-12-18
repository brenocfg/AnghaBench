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
struct fman_fpm_regs {int /*<<< orphan*/  fm_rcr; int /*<<< orphan*/  fm_rie; } ;

/* Variables and functions */
 int FPM_MURAM_ECC_ERR_EX_EN ; 
 int FPM_RAM_IRAM_ECC ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

uint32_t fman_get_muram_err_event(struct fman_fpm_regs *fpm_rg)
{
	uint32_t	event, mask;

	event = ioread32be(&fpm_rg->fm_rcr);
	mask = ioread32be(&fpm_rg->fm_rie);

	/* clear MURAM event bit (do not clear IRAM event) */
	iowrite32be(event & ~FPM_RAM_IRAM_ECC, &fpm_rg->fm_rcr);

	if ((mask & FPM_MURAM_ECC_ERR_EX_EN))
		return event;
	else
		return 0;
}