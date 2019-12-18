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
struct clk_multiplier {unsigned long shift; int flags; scalar_t__ width; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_MULTIPLIER_ZERO_BYPASS ; 
 unsigned long GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long clk_mult_readl (struct clk_multiplier*) ; 
 struct clk_multiplier* to_clk_multiplier (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_multiplier_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct clk_multiplier *mult = to_clk_multiplier(hw);
	unsigned long val;

	val = clk_mult_readl(mult) >> mult->shift;
	val &= GENMASK(mult->width - 1, 0);

	if (!val && mult->flags & CLK_MULTIPLIER_ZERO_BYPASS)
		val = 1;

	return parent_rate * val;
}