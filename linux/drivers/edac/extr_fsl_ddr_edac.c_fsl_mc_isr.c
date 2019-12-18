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
typedef  int /*<<< orphan*/  u32 ;
struct mem_ctl_info {struct fsl_mc_pdata* pvt_info; } ;
struct fsl_mc_pdata {scalar_t__ mc_vbase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ FSL_MC_ERR_DETECT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ddr_in32 (scalar_t__) ; 
 int /*<<< orphan*/  fsl_mc_check (struct mem_ctl_info*) ; 

__attribute__((used)) static irqreturn_t fsl_mc_isr(int irq, void *dev_id)
{
	struct mem_ctl_info *mci = dev_id;
	struct fsl_mc_pdata *pdata = mci->pvt_info;
	u32 err_detect;

	err_detect = ddr_in32(pdata->mc_vbase + FSL_MC_ERR_DETECT);
	if (!err_detect)
		return IRQ_NONE;

	fsl_mc_check(mci);

	return IRQ_HANDLED;
}