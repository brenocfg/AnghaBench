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
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_fpm_regs {int /*<<< orphan*/  fmfp_ee; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint32_t fman_get_fpm_err_event(struct fman_fpm_regs *fpm_rg)
{
	uint32_t	event;

	event = ioread32be(&fpm_rg->fmfp_ee);
	/* clear the all occurred events */
	iowrite32be(event, &fpm_rg->fmfp_ee);
	return event;
}