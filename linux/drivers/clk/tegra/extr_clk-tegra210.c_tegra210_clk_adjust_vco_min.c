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
struct tegra_clk_pll_params {unsigned long vco_min; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLL_SDM_COEFF ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long
tegra210_clk_adjust_vco_min(struct tegra_clk_pll_params *params,
			    unsigned long parent_rate)
{
	unsigned long vco_min = params->vco_min;

	params->vco_min += DIV_ROUND_UP(parent_rate, PLL_SDM_COEFF);
	vco_min = min(vco_min, params->vco_min);

	return vco_min;
}