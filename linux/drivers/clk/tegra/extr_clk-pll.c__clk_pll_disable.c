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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_clk_pll {TYPE_1__* params; scalar_t__ pmc; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int flags; scalar_t__ iddq_reg; int /*<<< orphan*/  iddq_bit_idx; scalar_t__ reset_reg; int /*<<< orphan*/  reset_bit_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLL_BASE_BYPASS ; 
 int /*<<< orphan*/  PLL_BASE_ENABLE ; 
 scalar_t__ PMC_PLLP_WB0_OVERRIDE ; 
 int /*<<< orphan*/  PMC_PLLP_WB0_OVERRIDE_PLLM_ENABLE ; 
 int TEGRA_PLLM ; 
 int TEGRA_PLL_BYPASS ; 
 int /*<<< orphan*/  pll_readl (scalar_t__,struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_readl_base (struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_writel (int /*<<< orphan*/ ,scalar_t__,struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_writel_base (int /*<<< orphan*/ ,struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct tegra_clk_pll* to_clk_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void _clk_pll_disable(struct clk_hw *hw)
{
	struct tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val;

	val = pll_readl_base(pll);
	if (pll->params->flags & TEGRA_PLL_BYPASS)
		val &= ~PLL_BASE_BYPASS;
	val &= ~PLL_BASE_ENABLE;
	pll_writel_base(val, pll);

	if (pll->params->flags & TEGRA_PLLM) {
		val = readl_relaxed(pll->pmc + PMC_PLLP_WB0_OVERRIDE);
		val &= ~PMC_PLLP_WB0_OVERRIDE_PLLM_ENABLE;
		writel_relaxed(val, pll->pmc + PMC_PLLP_WB0_OVERRIDE);
	}

	if (pll->params->reset_reg) {
		val = pll_readl(pll->params->reset_reg, pll);
		val |= BIT(pll->params->reset_bit_idx);
		pll_writel(val, pll->params->reset_reg, pll);
	}

	if (pll->params->iddq_reg) {
		val = pll_readl(pll->params->iddq_reg, pll);
		val |= BIT(pll->params->iddq_bit_idx);
		pll_writel(val, pll->params->iddq_reg, pll);
		udelay(2);
	}
}