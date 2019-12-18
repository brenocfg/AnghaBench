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
struct fman_bmi_regs {int /*<<< orphan*/  fmbm_ievr; int /*<<< orphan*/  fmbm_ifr; int /*<<< orphan*/  fmbm_ier; } ;

/* Variables and functions */
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

uint32_t fman_get_bmi_err_event(struct fman_bmi_regs *bmi_rg)
{
	uint32_t	event, mask, force;

	event = ioread32be(&bmi_rg->fmbm_ievr);
	mask = ioread32be(&bmi_rg->fmbm_ier);
	event &= mask;
	/* clear the forced events */
	force = ioread32be(&bmi_rg->fmbm_ifr);
	if (force & event)
		iowrite32be(force & ~event, &bmi_rg->fmbm_ifr);
	/* clear the acknowledged events */
	iowrite32be(event, &bmi_rg->fmbm_ievr);
	return event;
}