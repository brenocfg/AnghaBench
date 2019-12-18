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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_fpm_regs {int /*<<< orphan*/ * fmfp_cee; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 

uint32_t fman_get_ctrl_intr(struct fman_fpm_regs *fpm_rg, uint8_t event_reg_id)
{
	return ioread32be(&fpm_rg->fmfp_cee[event_reg_id]);
}