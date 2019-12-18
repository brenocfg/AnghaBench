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
struct fman_fpm_regs {int /*<<< orphan*/  fm_rcr; } ;

/* Variables and functions */
 int FPM_RAM_IRAM_ECC_EN ; 
 int FPM_RAM_RAMS_ECC_EN ; 
 int FPM_RAM_RAMS_ECC_EN_SRC_SEL ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_enable_rams_ecc(struct fman_fpm_regs *fpm_rg)
{
	uint32_t tmp;

	tmp = ioread32be(&fpm_rg->fm_rcr);
	if (tmp & FPM_RAM_RAMS_ECC_EN_SRC_SEL)
		iowrite32be(tmp | FPM_RAM_IRAM_ECC_EN,
				&fpm_rg->fm_rcr);
	else
		iowrite32be(tmp | FPM_RAM_RAMS_ECC_EN |
				FPM_RAM_IRAM_ECC_EN,
				&fpm_rg->fm_rcr);
}