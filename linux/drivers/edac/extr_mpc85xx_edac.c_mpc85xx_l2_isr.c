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
typedef  int u32 ;
struct mpc85xx_l2_pdata {scalar_t__ l2_vbase; } ;
struct edac_device_ctl_info {struct mpc85xx_l2_pdata* pvt_info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int L2_EDE_MASK ; 
 scalar_t__ MPC85XX_L2_ERRDET ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  mpc85xx_l2_check (struct edac_device_ctl_info*) ; 

__attribute__((used)) static irqreturn_t mpc85xx_l2_isr(int irq, void *dev_id)
{
	struct edac_device_ctl_info *edac_dev = dev_id;
	struct mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	u32 err_detect;

	err_detect = in_be32(pdata->l2_vbase + MPC85XX_L2_ERRDET);

	if (!(err_detect & L2_EDE_MASK))
		return IRQ_NONE;

	mpc85xx_l2_check(edac_dev);

	return IRQ_HANDLED;
}