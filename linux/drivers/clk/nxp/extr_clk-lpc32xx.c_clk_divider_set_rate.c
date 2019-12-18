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
struct lpc32xx_clk_div {int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  reg; int /*<<< orphan*/  flags; int /*<<< orphan*/  table; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_regmap ; 
 int div_mask (int /*<<< orphan*/ ) ; 
 unsigned int divider_get_val (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct lpc32xx_clk_div* to_lpc32xx_div (struct clk_hw*) ; 

__attribute__((used)) static int clk_divider_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct lpc32xx_clk_div *divider = to_lpc32xx_div(hw);
	unsigned int value;

	value = divider_get_val(rate, parent_rate, divider->table,
				divider->width, divider->flags);

	return regmap_update_bits(clk_regmap, divider->reg,
				  div_mask(divider->width) << divider->shift,
				  value << divider->shift);
}