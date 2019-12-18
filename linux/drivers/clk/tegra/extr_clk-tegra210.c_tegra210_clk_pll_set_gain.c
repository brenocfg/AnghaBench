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
struct tegra_clk_pll_freq_table {int /*<<< orphan*/  m; int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_SDM_COEFF ; 
 int /*<<< orphan*/  sdin_get_n_eff (struct tegra_clk_pll_freq_table*) ; 

__attribute__((used)) static void tegra210_clk_pll_set_gain(struct tegra_clk_pll_freq_table *cfg)
{
	cfg->n = sdin_get_n_eff(cfg);
	cfg->m *= PLL_SDM_COEFF;
}