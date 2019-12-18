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
struct meson_clk_pll_data {int /*<<< orphan*/  frac; int /*<<< orphan*/  m; int /*<<< orphan*/  n; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ MESON_PARM_APPLICABLE (int /*<<< orphan*/ *) ; 
 unsigned long __pll_params_to_rate (unsigned long,unsigned int,unsigned int,unsigned int,struct meson_clk_pll_data*) ; 
 struct meson_clk_pll_data* meson_clk_pll_data (struct clk_regmap*) ; 
 unsigned int meson_parm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static unsigned long meson_clk_pll_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	unsigned int m, n, frac;

	n = meson_parm_read(clk->map, &pll->n);
	m = meson_parm_read(clk->map, &pll->m);

	frac = MESON_PARM_APPLICABLE(&pll->frac) ?
		meson_parm_read(clk->map, &pll->frac) :
		0;

	return __pll_params_to_rate(parent_rate, m, n, frac, pll);
}