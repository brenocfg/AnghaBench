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
typedef  int uint64_t ;
struct clk_sccg_pll_setup {scalar_t__ divf1; int ref; int /*<<< orphan*/  bypass; scalar_t__ divr1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PLL_BYPASS_NONE ; 
 scalar_t__ PLL_DIVF1_MAX ; 
 int clk_sccg_pll2_find_setup (struct clk_sccg_pll_setup*,struct clk_sccg_pll_setup*,int) ; 
 int /*<<< orphan*/  do_div (int,scalar_t__) ; 

__attribute__((used)) static int clk_sccg_divf1_lookup(struct clk_sccg_pll_setup *setup,
				struct clk_sccg_pll_setup *temp_setup)
{
	int ret = -EINVAL;

	for (temp_setup->divf1 = 0; temp_setup->divf1 <= PLL_DIVF1_MAX;
	     temp_setup->divf1++) {
		uint64_t vco1 = temp_setup->ref;

		do_div(vco1, temp_setup->divr1 + 1);
		vco1 *= 2;
		vco1 *= temp_setup->divf1 + 1;

		ret = clk_sccg_pll2_find_setup(setup, temp_setup, vco1);
		if (!ret) {
			temp_setup->bypass = PLL_BYPASS_NONE;
			return ret;
		}
	}

	return ret;
}