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
typedef  int u32 ;
struct tegra_clk_pll_freq_table {int m; int n; int p; int cpcon; } ;
struct tegra_clk_pll {scalar_t__ clk_base; TYPE_1__* params; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  fixed_rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int PLLE_BASE_DIVCML_MASK ; 
 int PLLE_BASE_DIVCML_SHIFT ; 
 int PLLE_MISC_LOCK_ENABLE ; 
 int PLLE_MISC_READY ; 
 int PLLE_MISC_SETUP_MASK ; 
 int PLLE_MISC_SETUP_VALUE ; 
 int PLLE_SS_COEFFICIENTS_MASK ; 
 scalar_t__ PLLE_SS_CTRL ; 
 int PLLE_SS_DISABLE ; 
 int PLL_BASE_BYPASS ; 
 int PLL_BASE_ENABLE ; 
 int TEGRA_PLLE_CONFIGURE ; 
 scalar_t__ _get_table_rate (struct clk_hw*,struct tegra_clk_pll_freq_table*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clk_hw_get_parent (struct clk_hw*) ; 
 unsigned long clk_hw_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_pll_disable (struct clk_hw*) ; 
 scalar_t__ clk_pll_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_pll_wait_for_lock (struct tegra_clk_pll*) ; 
 int clk_plle_training (struct tegra_clk_pll*) ; 
 int divm_mask_shifted (struct tegra_clk_pll*) ; 
 int divm_shift (struct tegra_clk_pll*) ; 
 int divn_mask_shifted (struct tegra_clk_pll*) ; 
 int divn_shift (struct tegra_clk_pll*) ; 
 int divp_mask_shifted (struct tegra_clk_pll*) ; 
 int divp_shift (struct tegra_clk_pll*) ; 
 int pll_readl_base (struct tegra_clk_pll*) ; 
 int pll_readl_misc (struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_writel_base (int,struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_writel_misc (int,struct tegra_clk_pll*) ; 
 int readl (scalar_t__) ; 
 struct tegra_clk_pll* to_clk_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int clk_plle_enable(struct clk_hw *hw)
{
	struct tegra_clk_pll *pll = to_clk_pll(hw);
	struct tegra_clk_pll_freq_table sel;
	unsigned long input_rate;
	u32 val;
	int err;

	if (clk_pll_is_enabled(hw))
		return 0;

	input_rate = clk_hw_get_rate(clk_hw_get_parent(hw));

	if (_get_table_rate(hw, &sel, pll->params->fixed_rate, input_rate))
		return -EINVAL;

	clk_pll_disable(hw);

	val = pll_readl_misc(pll);
	val &= ~(PLLE_MISC_LOCK_ENABLE | PLLE_MISC_SETUP_MASK);
	pll_writel_misc(val, pll);

	val = pll_readl_misc(pll);
	if (!(val & PLLE_MISC_READY)) {
		err = clk_plle_training(pll);
		if (err)
			return err;
	}

	if (pll->params->flags & TEGRA_PLLE_CONFIGURE) {
		/* configure dividers */
		val = pll_readl_base(pll);
		val &= ~(divp_mask_shifted(pll) | divn_mask_shifted(pll) |
			 divm_mask_shifted(pll));
		val &= ~(PLLE_BASE_DIVCML_MASK << PLLE_BASE_DIVCML_SHIFT);
		val |= sel.m << divm_shift(pll);
		val |= sel.n << divn_shift(pll);
		val |= sel.p << divp_shift(pll);
		val |= sel.cpcon << PLLE_BASE_DIVCML_SHIFT;
		pll_writel_base(val, pll);
	}

	val = pll_readl_misc(pll);
	val |= PLLE_MISC_SETUP_VALUE;
	val |= PLLE_MISC_LOCK_ENABLE;
	pll_writel_misc(val, pll);

	val = readl(pll->clk_base + PLLE_SS_CTRL);
	val &= ~PLLE_SS_COEFFICIENTS_MASK;
	val |= PLLE_SS_DISABLE;
	writel(val, pll->clk_base + PLLE_SS_CTRL);

	val = pll_readl_base(pll);
	val |= (PLL_BASE_BYPASS | PLL_BASE_ENABLE);
	pll_writel_base(val, pll);

	clk_pll_wait_for_lock(pll);

	return 0;
}