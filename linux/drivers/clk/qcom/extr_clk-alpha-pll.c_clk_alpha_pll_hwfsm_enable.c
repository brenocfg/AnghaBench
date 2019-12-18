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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll {int flags; TYPE_1__ clkr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_FSM_ENA ; 
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_OFFLINE_REQ ; 
 int SUPPORTS_OFFLINE_REQ ; 
 int /*<<< orphan*/  mb () ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 
 int wait_for_pll_enable_active (struct clk_alpha_pll*) ; 

__attribute__((used)) static int clk_alpha_pll_hwfsm_enable(struct clk_hw *hw)
{
	int ret;
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;

	ret = regmap_read(pll->clkr.regmap, PLL_MODE(pll), &val);
	if (ret)
		return ret;

	val |= PLL_FSM_ENA;

	if (pll->flags & SUPPORTS_OFFLINE_REQ)
		val &= ~PLL_OFFLINE_REQ;

	ret = regmap_write(pll->clkr.regmap, PLL_MODE(pll), val);
	if (ret)
		return ret;

	/* Make sure enable request goes through before waiting for update */
	mb();

	return wait_for_pll_enable_active(pll);
}