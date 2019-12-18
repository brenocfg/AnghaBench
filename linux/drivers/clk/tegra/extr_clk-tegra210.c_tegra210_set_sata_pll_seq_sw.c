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
 scalar_t__ SATA_PLL_CFG0 ; 
 int /*<<< orphan*/  SATA_PLL_CFG0_SATA_SEQ_IN_SWCTL ; 
 int /*<<< orphan*/  SATA_PLL_CFG0_SATA_SEQ_LANE_PD_INPUT_VALUE ; 
 int /*<<< orphan*/  SATA_PLL_CFG0_SATA_SEQ_PADPLL_PD_INPUT_VALUE ; 
 int /*<<< orphan*/  SATA_PLL_CFG0_SATA_SEQ_RESET_INPUT_VALUE ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void tegra210_set_sata_pll_seq_sw(bool state)
{
	u32 val;

	val = readl_relaxed(clk_base + SATA_PLL_CFG0);
	if (state) {
		val |= SATA_PLL_CFG0_SATA_SEQ_IN_SWCTL;
		val |= SATA_PLL_CFG0_SATA_SEQ_RESET_INPUT_VALUE;
		val |= SATA_PLL_CFG0_SATA_SEQ_LANE_PD_INPUT_VALUE;
		val |= SATA_PLL_CFG0_SATA_SEQ_PADPLL_PD_INPUT_VALUE;
	} else {
		val &= ~SATA_PLL_CFG0_SATA_SEQ_IN_SWCTL;
		val &= ~SATA_PLL_CFG0_SATA_SEQ_RESET_INPUT_VALUE;
		val &= ~SATA_PLL_CFG0_SATA_SEQ_LANE_PD_INPUT_VALUE;
		val &= ~SATA_PLL_CFG0_SATA_SEQ_PADPLL_PD_INPUT_VALUE;
	}
	writel_relaxed(val, clk_base + SATA_PLL_CFG0);
}