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
struct clk_regmap {int /*<<< orphan*/  regmap; } ;
struct clk_regmap_div {int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  reg; struct clk_regmap clkr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_DIVIDER_ROUND_CLOSEST ; 
 long divider_ro_round_rate (struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_regmap_div* to_clk_regmap_div (struct clk_hw*) ; 

__attribute__((used)) static long div_round_ro_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long *prate)
{
	struct clk_regmap_div *divider = to_clk_regmap_div(hw);
	struct clk_regmap *clkr = &divider->clkr;
	u32 val;

	regmap_read(clkr->regmap, divider->reg, &val);
	val >>= divider->shift;
	val &= BIT(divider->width) - 1;

	return divider_ro_round_rate(hw, rate, prate, NULL, divider->width,
				     CLK_DIVIDER_ROUND_CLOSEST, val);
}