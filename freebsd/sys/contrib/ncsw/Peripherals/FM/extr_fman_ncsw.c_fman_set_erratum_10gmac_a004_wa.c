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
struct fman_fpm_regs {int /*<<< orphan*/  fmfp_extc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_set_erratum_10gmac_a004_wa(struct fman_fpm_regs *fpm_rg)
{
	int timeout = 100;

	iowrite32be(0x40000000, &fpm_rg->fmfp_extc);

	while ((ioread32be(&fpm_rg->fmfp_extc) & 0x40000000) && --timeout)
		DELAY(10);

	if (!timeout)
		return -EBUSY;
	return 0;
}