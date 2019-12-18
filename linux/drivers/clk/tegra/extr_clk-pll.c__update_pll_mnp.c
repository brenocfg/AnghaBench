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
typedef  int u32 ;
struct tegra_clk_pll_params {int flags; int /*<<< orphan*/  pmc_divnm_reg; int /*<<< orphan*/  pmc_divp_reg; struct div_nmp* div_nmp; } ;
struct tegra_clk_pll_freq_table {int p; int m; int n; } ;
struct tegra_clk_pll {int /*<<< orphan*/  hw; struct tegra_clk_pll_params* params; } ;
struct div_nmp {int override_divp_shift; int override_divm_shift; int override_divn_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_PLLP_WB0_OVERRIDE ; 
 int PMC_PLLP_WB0_OVERRIDE_PLLM_OVERRIDE ; 
 int TEGRA_PLLM ; 
 int TEGRA_PLLMB ; 
 int /*<<< orphan*/  clk_pll_set_sdm_data (int /*<<< orphan*/ *,struct tegra_clk_pll_freq_table*) ; 
 int divm_mask (struct tegra_clk_pll*) ; 
 int divm_mask_shifted (struct tegra_clk_pll*) ; 
 int divm_shift (struct tegra_clk_pll*) ; 
 int divn_mask (struct tegra_clk_pll*) ; 
 int divn_mask_shifted (struct tegra_clk_pll*) ; 
 int divn_shift (struct tegra_clk_pll*) ; 
 int divp_mask (struct tegra_clk_pll*) ; 
 int divp_mask_shifted (struct tegra_clk_pll*) ; 
 int divp_shift (struct tegra_clk_pll*) ; 
 int pll_override_readl (int /*<<< orphan*/ ,struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_override_writel (int,int /*<<< orphan*/ ,struct tegra_clk_pll*) ; 
 int pll_readl_base (struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_writel_base (int,struct tegra_clk_pll*) ; 

__attribute__((used)) static void _update_pll_mnp(struct tegra_clk_pll *pll,
			    struct tegra_clk_pll_freq_table *cfg)
{
	u32 val;
	struct tegra_clk_pll_params *params = pll->params;
	struct div_nmp *div_nmp = params->div_nmp;

	if ((params->flags & (TEGRA_PLLM | TEGRA_PLLMB)) &&
		(pll_override_readl(PMC_PLLP_WB0_OVERRIDE, pll) &
			PMC_PLLP_WB0_OVERRIDE_PLLM_OVERRIDE)) {
		val = pll_override_readl(params->pmc_divp_reg, pll);
		val &= ~(divp_mask(pll) << div_nmp->override_divp_shift);
		val |= cfg->p << div_nmp->override_divp_shift;
		pll_override_writel(val, params->pmc_divp_reg, pll);

		val = pll_override_readl(params->pmc_divnm_reg, pll);
		val &= ~((divm_mask(pll) << div_nmp->override_divm_shift) |
			(divn_mask(pll) << div_nmp->override_divn_shift));
		val |= (cfg->m << div_nmp->override_divm_shift) |
			(cfg->n << div_nmp->override_divn_shift);
		pll_override_writel(val, params->pmc_divnm_reg, pll);
	} else {
		val = pll_readl_base(pll);

		val &= ~(divm_mask_shifted(pll) | divn_mask_shifted(pll) |
			 divp_mask_shifted(pll));

		val |= (cfg->m << divm_shift(pll)) |
		       (cfg->n << divn_shift(pll)) |
		       (cfg->p << divp_shift(pll));

		pll_writel_base(val, pll);

		clk_pll_set_sdm_data(&pll->hw, cfg);
	}
}