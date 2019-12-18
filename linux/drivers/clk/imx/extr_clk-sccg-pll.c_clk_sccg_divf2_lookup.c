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
struct clk_sccg_pll_setup {scalar_t__ divf2; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PLL_DIVF2_MAX ; 
 int clk_sccg_divq_lookup (struct clk_sccg_pll_setup*,struct clk_sccg_pll_setup*) ; 

__attribute__((used)) static int clk_sccg_divf2_lookup(struct clk_sccg_pll_setup *setup,
					struct clk_sccg_pll_setup *temp_setup)
{
	int ret = -EINVAL;

	for (temp_setup->divf2 = 0; temp_setup->divf2 <= PLL_DIVF2_MAX;
	     temp_setup->divf2++) {
		ret = clk_sccg_divq_lookup(setup, temp_setup);
		if (!ret)
			return ret;
	}

	return ret;
}