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
struct clk_sccg_pll_setup {scalar_t__ divr2; scalar_t__ ref_div2; scalar_t__ vco1; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PLL_DIVR2_MAX ; 
 scalar_t__ PLL_STAGE2_REF_MAX_FREQ ; 
 scalar_t__ PLL_STAGE2_REF_MIN_FREQ ; 
 int clk_sccg_divf2_lookup (struct clk_sccg_pll_setup*,struct clk_sccg_pll_setup*) ; 
 int /*<<< orphan*/  do_div (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int clk_sccg_divr2_lookup(struct clk_sccg_pll_setup *setup,
				struct clk_sccg_pll_setup *temp_setup)
{
	int ret = -EINVAL;

	for (temp_setup->divr2 = 0; temp_setup->divr2 <= PLL_DIVR2_MAX;
	     temp_setup->divr2++) {
		temp_setup->ref_div2 = temp_setup->vco1;
		do_div(temp_setup->ref_div2, temp_setup->divr2 + 1);
		if (temp_setup->ref_div2 >= PLL_STAGE2_REF_MIN_FREQ &&
		    temp_setup->ref_div2 <= PLL_STAGE2_REF_MAX_FREQ) {
			ret = clk_sccg_divf2_lookup(setup, temp_setup);
			if (!ret)
				return ret;
		}
	}

	return ret;
}