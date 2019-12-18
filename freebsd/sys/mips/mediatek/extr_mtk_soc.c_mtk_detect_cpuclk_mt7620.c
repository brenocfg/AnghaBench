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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int MT7620_CPLL_SW_CFG ; 
 int MT7620_CPU_CLK_AUX0 ; 
 scalar_t__ MT7620_PLL_DIV_RATIO_BASE ; 
 int MT7620_PLL_DIV_RATIO_MAX ; 
 int MT7620_PLL_DIV_RATIO_MSK ; 
 int MT7620_PLL_DIV_RATIO_OFF ; 
 int MT7620_PLL_MULT_RATIO_BASE ; 
 int MT7620_PLL_MULT_RATIO_MSK ; 
 int MT7620_PLL_MULT_RATIO_OFF ; 
 int MT7620_XTAL_40 ; 
 int MTK_CPU_CLK_480MHZ ; 
 int MTK_CPU_CLK_600MHZ ; 
 int MTK_MHZ (int) ; 
 int /*<<< orphan*/  SYSCTL_MT7620_CPLL_CFG0 ; 
 int /*<<< orphan*/  SYSCTL_MT7620_CPLL_CFG1 ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
mtk_detect_cpuclk_mt7620(bus_space_tag_t bst, bus_space_handle_t bsh)
{
	uint32_t val, mul, div, res;

	val = bus_space_read_4(bst, bsh, SYSCTL_MT7620_CPLL_CFG1);
	if (val & MT7620_CPU_CLK_AUX0)
		return (MTK_CPU_CLK_480MHZ);

	val = bus_space_read_4(bst, bsh, SYSCTL_MT7620_CPLL_CFG0);
	if (!(val & MT7620_CPLL_SW_CFG))
		return (MTK_CPU_CLK_600MHZ);

	mul = MT7620_PLL_MULT_RATIO_BASE + ((val >> MT7620_PLL_MULT_RATIO_OFF) &
	    MT7620_PLL_MULT_RATIO_MSK);
	div = (val >> MT7620_PLL_DIV_RATIO_OFF) & MT7620_PLL_DIV_RATIO_MSK;

	if (div != MT7620_PLL_DIV_RATIO_MSK)
		div += MT7620_PLL_DIV_RATIO_BASE;
	else
		div = MT7620_PLL_DIV_RATIO_MAX;

	res = (MT7620_XTAL_40 * mul) / div;

	return (MTK_MHZ(res));
}