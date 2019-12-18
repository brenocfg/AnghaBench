#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_clk_pll_freq_table {unsigned long m; unsigned long output_rate; unsigned long n; unsigned long input_rate; int p; } ;
struct tegra_clk_pll {TYPE_1__* params; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long vco_max; int /*<<< orphan*/  vco_min; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned long) ; 
 int EINVAL ; 
 int _p_div_to_hw (struct clk_hw*,unsigned int) ; 
 unsigned long _pll_fixed_mdiv (TYPE_1__*,unsigned long) ; 
 scalar_t__ divn_max (struct tegra_clk_pll*) ; 
 struct tegra_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static int _calc_dynamic_ramp_rate(struct clk_hw *hw,
				struct tegra_clk_pll_freq_table *cfg,
				unsigned long rate, unsigned long parent_rate)
{
	struct tegra_clk_pll *pll = to_clk_pll(hw);
	unsigned int p;
	int p_div;

	if (!rate)
		return -EINVAL;

	p = DIV_ROUND_UP(pll->params->vco_min, rate);
	cfg->m = _pll_fixed_mdiv(pll->params, parent_rate);
	cfg->output_rate = rate * p;
	cfg->n = cfg->output_rate * cfg->m / parent_rate;
	cfg->input_rate = parent_rate;

	p_div = _p_div_to_hw(hw, p);
	if (p_div < 0)
		return p_div;

	cfg->p = p_div;

	if (cfg->n > divn_max(pll) || cfg->output_rate > pll->params->vco_max)
		return -EINVAL;

	return 0;
}