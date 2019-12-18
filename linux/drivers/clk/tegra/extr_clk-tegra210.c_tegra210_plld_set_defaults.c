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
 int PLLD_MISC0_DEFAULT_VALUE ; 
 int PLLD_MISC0_DSI_CLKENABLE ; 
 int PLLD_MISC0_EN_SDM ; 
 int PLLD_MISC0_IDDQ ; 
 int PLLD_MISC0_LOCK_ENABLE ; 
 int PLLD_MISC0_LOCK_OVERRIDE ; 
 int PLLD_MISC0_WRITE_MASK ; 
 int PLLD_MISC1_DEFAULT_VALUE ; 
 int PLLD_MISC1_WRITE_MASK ; 
 int PLL_ENABLE ; 
 int /*<<< orphan*/  _pll_misc_chk_default (scalar_t__,TYPE_1__*,int,int,int) ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void tegra210_plld_set_defaults(struct tegra_clk_pll *plld)
{
	u32 val;
	u32 mask = 0xffff;

	plld->params->defaults_set = true;

	if (readl_relaxed(clk_base + plld->params->base_reg) &
			PLL_ENABLE) {

		/*
		 * PLL is ON: check if defaults already set, then set those
		 * that can be updated in flight.
		 */
		val = PLLD_MISC1_DEFAULT_VALUE;
		_pll_misc_chk_default(clk_base, plld->params, 1,
				val, PLLD_MISC1_WRITE_MASK);

		/* ignore lock, DSI and SDM controls, make sure IDDQ not set */
		val = PLLD_MISC0_DEFAULT_VALUE & (~PLLD_MISC0_IDDQ);
		mask |= PLLD_MISC0_DSI_CLKENABLE | PLLD_MISC0_LOCK_ENABLE |
			PLLD_MISC0_LOCK_OVERRIDE | PLLD_MISC0_EN_SDM;
		_pll_misc_chk_default(clk_base, plld->params, 0, val,
				~mask & PLLD_MISC0_WRITE_MASK);

		if (!plld->params->defaults_set)
			pr_warn("PLL_D already enabled. Postponing set full defaults\n");

		/* Enable lock detect */
		mask = PLLD_MISC0_LOCK_ENABLE | PLLD_MISC0_LOCK_OVERRIDE;
		val = readl_relaxed(clk_base + plld->params->ext_misc_reg[0]);
		val &= ~mask;
		val |= PLLD_MISC0_DEFAULT_VALUE & mask;
		writel_relaxed(val, clk_base + plld->params->ext_misc_reg[0]);
		udelay(1);

		return;
	}

	val = readl_relaxed(clk_base + plld->params->ext_misc_reg[0]);
	val &= PLLD_MISC0_DSI_CLKENABLE;
	val |= PLLD_MISC0_DEFAULT_VALUE;
	/* set IDDQ, enable lock detect, disable SDM */
	writel_relaxed(val, clk_base + plld->params->ext_misc_reg[0]);
	writel_relaxed(PLLD_MISC1_DEFAULT_VALUE, clk_base +
			plld->params->ext_misc_reg[1]);
	udelay(1);
}