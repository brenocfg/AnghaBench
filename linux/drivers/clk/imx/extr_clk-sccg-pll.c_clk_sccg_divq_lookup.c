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
struct clk_sccg_pll_setup {int divq; int vco2; int vco1; int divr2; int divf2; int fout; int /*<<< orphan*/  bypass; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PLL_BYPASS1 ; 
 int PLL_DIVQ_MAX ; 
 int PLL_STAGE2_MAX_FREQ ; 
 int PLL_STAGE2_MIN_FREQ ; 
 int clk_sccg_pll2_check_match (struct clk_sccg_pll_setup*,struct clk_sccg_pll_setup*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static int clk_sccg_divq_lookup(struct clk_sccg_pll_setup *setup,
				struct clk_sccg_pll_setup *temp_setup)
{
	int ret = -EINVAL;

	for (temp_setup->divq = 0; temp_setup->divq <= PLL_DIVQ_MAX;
	     temp_setup->divq++) {
		temp_setup->vco2 = temp_setup->vco1;
		do_div(temp_setup->vco2, temp_setup->divr2 + 1);
		temp_setup->vco2 *= 2;
		temp_setup->vco2 *= temp_setup->divf2 + 1;
		if (temp_setup->vco2 >= PLL_STAGE2_MIN_FREQ &&
				temp_setup->vco2 <= PLL_STAGE2_MAX_FREQ) {
			temp_setup->fout = temp_setup->vco2;
			do_div(temp_setup->fout, 2 * (temp_setup->divq + 1));

			ret = clk_sccg_pll2_check_match(setup, temp_setup);
			if (!ret) {
				temp_setup->bypass = PLL_BYPASS1;
				return ret;
			}
		}
	}

	return ret;
}