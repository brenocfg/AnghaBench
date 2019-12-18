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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int CNS3XXX_PWR_PLL_ALL ; 
 int /*<<< orphan*/  PM_PLL_HM_PD_CTRL_REG ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void cns3xxx_pwr_power_up(unsigned int block)
{
	u32 reg = __raw_readl(PM_PLL_HM_PD_CTRL_REG);

	reg &= ~(block & CNS3XXX_PWR_PLL_ALL);
	__raw_writel(reg, PM_PLL_HM_PD_CTRL_REG);

	/* Wait for 300us for the PLL output clock locked. */
	udelay(300);
}