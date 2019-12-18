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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 
 int trion_pll_is_enabled (struct clk_alpha_pll*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_trion_pll_is_enabled(struct clk_hw *hw)
{
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);

	return trion_pll_is_enabled(pll, pll->clkr.regmap);
}