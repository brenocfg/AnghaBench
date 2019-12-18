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
struct clk_regmap {unsigned int enable_mask; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  regmap; scalar_t__ enable_is_inverted; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

int clk_enable_regmap(struct clk_hw *hw)
{
	struct clk_regmap *rclk = to_clk_regmap(hw);
	unsigned int val;

	if (rclk->enable_is_inverted)
		val = 0;
	else
		val = rclk->enable_mask;

	return regmap_update_bits(rclk->regmap, rclk->enable_reg,
				  rclk->enable_mask, val);
}