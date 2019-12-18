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
typedef  int uint32_t ;
struct fman_fpm_regs {int /*<<< orphan*/ * fmfp_cev; int /*<<< orphan*/ * fmfp_cee; int /*<<< orphan*/ * fmfp_fcev; } ;

/* Variables and functions */
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

uint32_t fman_get_controller_event(struct fman_fpm_regs *fpm_rg, uint8_t reg_id)
{
	uint32_t event;

	event = ioread32be(&fpm_rg->fmfp_fcev[reg_id]) &
			ioread32be(&fpm_rg->fmfp_cee[reg_id]);
	iowrite32be(event, &fpm_rg->fmfp_cev[reg_id]);

	return event;
}