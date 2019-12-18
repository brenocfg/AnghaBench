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
struct meson_clk_mpll_data {int /*<<< orphan*/  n2; int /*<<< orphan*/  sdm; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct meson_clk_mpll_data* meson_clk_mpll_data (struct clk_regmap*) ; 
 unsigned int meson_parm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long rate_from_params (unsigned long,unsigned int,unsigned int) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static unsigned long mpll_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_mpll_data *mpll = meson_clk_mpll_data(clk);
	unsigned int sdm, n2;
	long rate;

	sdm = meson_parm_read(clk->map, &mpll->sdm);
	n2 = meson_parm_read(clk->map, &mpll->n2);

	rate = rate_from_params(parent_rate, sdm, n2);
	return rate < 0 ? 0 : rate;
}