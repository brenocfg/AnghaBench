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
struct mem_ctl_info {struct cpc925_mc_pdata* pvt_info; } ;
struct cpc925_mc_pdata {scalar_t__ vbase; } ;

/* Variables and functions */
 int ECC_MASK_ENABLE ; 
 int MCCR_ECC_EN ; 
 scalar_t__ REG_APIMASK_OFFSET ; 
 scalar_t__ REG_MCCR_OFFSET ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

__attribute__((used)) static void cpc925_mc_init(struct mem_ctl_info *mci)
{
	struct cpc925_mc_pdata *pdata = mci->pvt_info;
	u32 apimask;
	u32 mccr;

	/* Enable various ECC error exceptions */
	apimask = __raw_readl(pdata->vbase + REG_APIMASK_OFFSET);
	if ((apimask & ECC_MASK_ENABLE) == 0) {
		apimask |= ECC_MASK_ENABLE;
		__raw_writel(apimask, pdata->vbase + REG_APIMASK_OFFSET);
	}

	/* Enable ECC detection */
	mccr = __raw_readl(pdata->vbase + REG_MCCR_OFFSET);
	if ((mccr & MCCR_ECC_EN) == 0) {
		mccr |= MCCR_ECC_EN;
		__raw_writel(mccr, pdata->vbase + REG_MCCR_OFFSET);
	}
}