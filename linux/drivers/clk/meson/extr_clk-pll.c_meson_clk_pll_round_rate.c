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
struct meson_clk_pll_data {int /*<<< orphan*/  frac; } ;
struct clk_regmap {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_PARM_APPLICABLE (int /*<<< orphan*/ *) ; 
 long __pll_params_to_rate (unsigned long,unsigned int,unsigned int,unsigned int,struct meson_clk_pll_data*) ; 
 unsigned int __pll_params_with_frac (unsigned long,unsigned long,unsigned int,unsigned int,struct meson_clk_pll_data*) ; 
 int meson_clk_get_pll_settings (unsigned long,unsigned long,unsigned int*,unsigned int*,struct meson_clk_pll_data*) ; 
 struct meson_clk_pll_data* meson_clk_pll_data (struct clk_regmap*) ; 
 long meson_clk_pll_recalc_rate (struct clk_hw*,unsigned long) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static long meson_clk_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *parent_rate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	unsigned int m, n, frac;
	unsigned long round;
	int ret;

	ret = meson_clk_get_pll_settings(rate, *parent_rate, &m, &n, pll);
	if (ret)
		return meson_clk_pll_recalc_rate(hw, *parent_rate);

	round = __pll_params_to_rate(*parent_rate, m, n, 0, pll);

	if (!MESON_PARM_APPLICABLE(&pll->frac) || rate == round)
		return round;

	/*
	 * The rate provided by the setting is not an exact match, let's
	 * try to improve the result using the fractional parameter
	 */
	frac = __pll_params_with_frac(rate, *parent_rate, m, n, pll);

	return __pll_params_to_rate(*parent_rate, m, n, frac, pll);
}