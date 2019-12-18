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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OSC_CTRL ; 
#define  OSC_CTRL_OSC_FREQ_12MHZ 131 
#define  OSC_CTRL_OSC_FREQ_13MHZ 130 
#define  OSC_CTRL_OSC_FREQ_19_2MHZ 129 
#define  OSC_CTRL_OSC_FREQ_26MHZ 128 
 int OSC_CTRL_OSC_FREQ_MASK ; 
 int OSC_CTRL_PLL_REF_DIV_1 ; 
 int OSC_CTRL_PLL_REF_DIV_MASK ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static unsigned long tegra20_clk_measure_input_freq(void)
{
	u32 osc_ctrl = readl_relaxed(clk_base + OSC_CTRL);
	u32 auto_clk_control = osc_ctrl & OSC_CTRL_OSC_FREQ_MASK;
	u32 pll_ref_div = osc_ctrl & OSC_CTRL_PLL_REF_DIV_MASK;
	unsigned long input_freq;

	switch (auto_clk_control) {
	case OSC_CTRL_OSC_FREQ_12MHZ:
		BUG_ON(pll_ref_div != OSC_CTRL_PLL_REF_DIV_1);
		input_freq = 12000000;
		break;
	case OSC_CTRL_OSC_FREQ_13MHZ:
		BUG_ON(pll_ref_div != OSC_CTRL_PLL_REF_DIV_1);
		input_freq = 13000000;
		break;
	case OSC_CTRL_OSC_FREQ_19_2MHZ:
		BUG_ON(pll_ref_div != OSC_CTRL_PLL_REF_DIV_1);
		input_freq = 19200000;
		break;
	case OSC_CTRL_OSC_FREQ_26MHZ:
		BUG_ON(pll_ref_div != OSC_CTRL_PLL_REF_DIV_1);
		input_freq = 26000000;
		break;
	default:
		pr_err("Unexpected clock autodetect value %d",
		       auto_clk_control);
		BUG();
		return 0;
	}

	return input_freq;
}