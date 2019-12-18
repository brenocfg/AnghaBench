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
struct regmap {int dummy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FABIA_OPMODE_STANDBY ; 
 int /*<<< orphan*/  FABIA_PLL_OUT_MASK ; 
 int PLL_FSM_ENA ; 
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_OPMODE (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_OUTCTRL ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  clk_disable_regmap (struct clk_hw*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 

__attribute__((used)) static void alpha_pll_fabia_disable(struct clk_hw *hw)
{
	int ret;
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;
	struct regmap *regmap = pll->clkr.regmap;

	ret = regmap_read(regmap, PLL_MODE(pll), &val);
	if (ret)
		return;

	/* If in FSM mode, just unvote it */
	if (val & PLL_FSM_ENA) {
		clk_disable_regmap(hw);
		return;
	}

	ret = regmap_update_bits(regmap, PLL_MODE(pll), PLL_OUTCTRL, 0);
	if (ret)
		return;

	/* Disable main outputs */
	ret = regmap_update_bits(regmap, PLL_USER_CTL(pll), FABIA_PLL_OUT_MASK,
				 0);
	if (ret)
		return;

	/* Place the PLL in STANDBY */
	regmap_write(regmap, PLL_OPMODE(pll), FABIA_OPMODE_STANDBY);
}