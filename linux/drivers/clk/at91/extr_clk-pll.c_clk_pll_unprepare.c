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
struct clk_pll {int /*<<< orphan*/  id; int /*<<< orphan*/  regmap; TYPE_1__* layout; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned int pllr_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static void clk_pll_unprepare(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);
	unsigned int mask = pll->layout->pllr_mask;

	regmap_update_bits(pll->regmap, PLL_REG(pll->id), mask, ~mask);
}