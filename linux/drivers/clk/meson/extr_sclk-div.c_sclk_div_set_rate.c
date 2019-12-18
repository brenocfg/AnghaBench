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
struct meson_sclk_div_data {int /*<<< orphan*/  cached_div; } ;
struct clk_regmap {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ clk_hw_is_enabled (struct clk_hw*) ; 
 struct meson_sclk_div_data* meson_sclk_div_data (struct clk_regmap*) ; 
 int /*<<< orphan*/  sclk_apply_divider (struct clk_regmap*,struct meson_sclk_div_data*) ; 
 int /*<<< orphan*/  sclk_div_getdiv (struct clk_hw*,unsigned long,unsigned long,unsigned long) ; 
 unsigned long sclk_div_maxdiv (struct meson_sclk_div_data*) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static int sclk_div_set_rate(struct clk_hw *hw, unsigned long rate,
			     unsigned long prate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_sclk_div_data *sclk = meson_sclk_div_data(clk);
	unsigned long maxdiv = sclk_div_maxdiv(sclk);

	sclk->cached_div = sclk_div_getdiv(hw, rate, prate, maxdiv);

	if (clk_hw_is_enabled(hw))
		sclk_apply_divider(clk, sclk);

	return 0;
}