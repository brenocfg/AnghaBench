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
struct fman_fpm_regs {int /*<<< orphan*/  fm_rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_RSTC_FM_RESET ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_reset(struct fman_fpm_regs *fpm_rg)
{
	iowrite32be(FPM_RSTC_FM_RESET, &fpm_rg->fm_rstc);
}