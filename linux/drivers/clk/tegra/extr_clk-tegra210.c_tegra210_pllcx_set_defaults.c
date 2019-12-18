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
struct tegra_clk_pll {TYPE_1__* params; } ;
struct TYPE_2__ {int defaults_set; scalar_t__* ext_misc_reg; scalar_t__ base_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLLCX_MISC0_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLCX_MISC1_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLCX_MISC2_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLCX_MISC3_DEFAULT_VALUE ; 
 int PLL_ENABLE ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  pllcx_check_defaults (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tegra210_pllcx_set_defaults(const char *name,
					struct tegra_clk_pll *pllcx)
{
	pllcx->params->defaults_set = true;

	if (readl_relaxed(clk_base + pllcx->params->base_reg) & PLL_ENABLE) {
		/* PLL is ON: only check if defaults already set */
		pllcx_check_defaults(pllcx->params);
		if (!pllcx->params->defaults_set)
			pr_warn("%s already enabled. Postponing set full defaults\n",
				name);
		return;
	}

	/* Defaults assert PLL reset, and set IDDQ */
	writel_relaxed(PLLCX_MISC0_DEFAULT_VALUE,
			clk_base + pllcx->params->ext_misc_reg[0]);
	writel_relaxed(PLLCX_MISC1_DEFAULT_VALUE,
			clk_base + pllcx->params->ext_misc_reg[1]);
	writel_relaxed(PLLCX_MISC2_DEFAULT_VALUE,
			clk_base + pllcx->params->ext_misc_reg[2]);
	writel_relaxed(PLLCX_MISC3_DEFAULT_VALUE,
			clk_base + pllcx->params->ext_misc_reg[3]);
	udelay(1);
}