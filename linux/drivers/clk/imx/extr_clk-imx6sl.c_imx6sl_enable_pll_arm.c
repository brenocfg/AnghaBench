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

/* Variables and functions */
 int /*<<< orphan*/  BM_PLL_ARM_ENABLE ; 
 int BM_PLL_ARM_LOCK ; 
 int /*<<< orphan*/  BM_PLL_ARM_POWERDOWN ; 
 scalar_t__ PLL_ARM ; 
 int __raw_readl (scalar_t__) ; 
 scalar_t__ anatop_base ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void imx6sl_enable_pll_arm(bool enable)
{
	static u32 saved_pll_arm;
	u32 val;

	if (enable) {
		saved_pll_arm = val = readl_relaxed(anatop_base + PLL_ARM);
		val |= BM_PLL_ARM_ENABLE;
		val &= ~BM_PLL_ARM_POWERDOWN;
		writel_relaxed(val, anatop_base + PLL_ARM);
		while (!(__raw_readl(anatop_base + PLL_ARM) & BM_PLL_ARM_LOCK))
			;
	} else {
		 writel_relaxed(saved_pll_arm, anatop_base + PLL_ARM);
	}
}