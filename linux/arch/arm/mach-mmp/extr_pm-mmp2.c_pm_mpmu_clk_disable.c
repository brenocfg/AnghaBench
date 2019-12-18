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
 int /*<<< orphan*/  MPMU_CGR_PJ ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm_mpmu_clk_disable(void)
{
	/*
	 * disable clocks in MPMU_CGR_PJ register
	 * except clock for APMU_PLL1, APMU_PLL1_2 and AP_26M
	 */
	__raw_writel(0x0000a010, MPMU_CGR_PJ);
}