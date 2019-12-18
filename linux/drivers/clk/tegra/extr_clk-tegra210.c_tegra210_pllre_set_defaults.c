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
struct tegra_clk_pll {TYPE_1__* params; } ;
struct TYPE_2__ {int defaults_set; scalar_t__* ext_misc_reg; scalar_t__ base_reg; } ;

/* Variables and functions */
 int PLLRE_BASE_DEFAULT_MASK ; 
 int PLLRE_BASE_DEFAULT_VALUE ; 
 int PLLRE_MISC0_DEFAULT_VALUE ; 
 int PLLRE_MISC0_IDDQ ; 
 int PLLRE_MISC0_LOCK_ENABLE ; 
 int PLLRE_MISC0_LOCK_OVERRIDE ; 
 int PLLRE_MISC0_WRITE_MASK ; 
 int PLL_ENABLE ; 
 int /*<<< orphan*/  _pll_misc_chk_default (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void tegra210_pllre_set_defaults(struct tegra_clk_pll *pllre)
{
	u32 mask;
	u32 val = readl_relaxed(clk_base + pllre->params->base_reg);

	pllre->params->defaults_set = true;

	if (val & PLL_ENABLE) {
		/*
		 * PLL is ON: check if defaults already set, then set those
		 * that can be updated in flight.
		 */
		val &= PLLRE_BASE_DEFAULT_MASK;
		if (val != PLLRE_BASE_DEFAULT_VALUE) {
			pr_warn("pllre boot base 0x%x : expected 0x%x\n",
				val, PLLRE_BASE_DEFAULT_VALUE);
			pr_warn("(comparison mask = 0x%x)\n",
				PLLRE_BASE_DEFAULT_MASK);
			pllre->params->defaults_set = false;
		}

		/* Ignore lock enable */
		val = PLLRE_MISC0_DEFAULT_VALUE & (~PLLRE_MISC0_IDDQ);
		mask = PLLRE_MISC0_LOCK_ENABLE | PLLRE_MISC0_LOCK_OVERRIDE;
		_pll_misc_chk_default(clk_base, pllre->params, 0, val,
				~mask & PLLRE_MISC0_WRITE_MASK);

		/* The PLL doesn't work if it's in IDDQ. */
		val = readl_relaxed(clk_base + pllre->params->ext_misc_reg[0]);
		if (val & PLLRE_MISC0_IDDQ)
			pr_warn("unexpected IDDQ bit set for enabled clock\n");

		/* Enable lock detect */
		val &= ~mask;
		val |= PLLRE_MISC0_DEFAULT_VALUE & mask;
		writel_relaxed(val, clk_base + pllre->params->ext_misc_reg[0]);
		udelay(1);

		if (!pllre->params->defaults_set)
			pr_warn("PLL_RE already enabled. Postponing set full defaults\n");

		return;
	}

	/* set IDDQ, enable lock detect */
	val &= ~PLLRE_BASE_DEFAULT_MASK;
	val |= PLLRE_BASE_DEFAULT_VALUE & PLLRE_BASE_DEFAULT_MASK;
	writel_relaxed(val, clk_base + pllre->params->base_reg);
	writel_relaxed(PLLRE_MISC0_DEFAULT_VALUE,
			clk_base + pllre->params->ext_misc_reg[0]);
	udelay(1);
}