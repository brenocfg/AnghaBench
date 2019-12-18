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
struct mv64x60_mc_pdata {scalar_t__ mc_vbase; } ;
struct mem_ctl_info {struct mv64x60_mc_pdata* pvt_info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MV64X60_SDRAM_ERR_ADDR ; 
 int /*<<< orphan*/  mv64x60_mc_check (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t mv64x60_mc_isr(int irq, void *dev_id)
{
	struct mem_ctl_info *mci = dev_id;
	struct mv64x60_mc_pdata *pdata = mci->pvt_info;
	u32 reg;

	reg = readl(pdata->mc_vbase + MV64X60_SDRAM_ERR_ADDR);
	if (!reg)
		return IRQ_NONE;

	/* writing 0's to the ECC err addr in check function clears irq */
	mv64x60_mc_check(mci);

	return IRQ_HANDLED;
}