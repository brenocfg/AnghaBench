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

/* Variables and functions */
 int ARM_WAIT_DIV_396M ; 
 int ARM_WAIT_DIV_792M ; 
 int ARM_WAIT_DIV_996M ; 
 int BM_CCSR_PLL1_SW_CLK_SEL ; 
 int BM_PLL_ARM_DIV_SELECT ; 
 scalar_t__ CCSR ; 
 scalar_t__ PLL_ARM ; 
 int PLL_ARM_DIV_792M ; 
 scalar_t__ anatop_base ; 
 scalar_t__ ccm_base ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int imx6sl_get_arm_divider_for_wait(void)
{
	if (readl_relaxed(ccm_base + CCSR) & BM_CCSR_PLL1_SW_CLK_SEL) {
		return ARM_WAIT_DIV_396M;
	} else {
		if ((readl_relaxed(anatop_base + PLL_ARM) &
			BM_PLL_ARM_DIV_SELECT) == PLL_ARM_DIV_792M)
			return ARM_WAIT_DIV_792M;
		else
			return ARM_WAIT_DIV_996M;
	}
}