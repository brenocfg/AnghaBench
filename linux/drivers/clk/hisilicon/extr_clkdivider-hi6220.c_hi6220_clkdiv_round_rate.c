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
struct hi6220_clk_divider {int /*<<< orphan*/  width; int /*<<< orphan*/  table; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_DIVIDER_ROUND_CLOSEST ; 
 long divider_round_rate (struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hi6220_clk_divider* to_hi6220_clk_divider (struct clk_hw*) ; 

__attribute__((used)) static long hi6220_clkdiv_round_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long *prate)
{
	struct hi6220_clk_divider *dclk = to_hi6220_clk_divider(hw);

	return divider_round_rate(hw, rate, prate, dclk->table,
				  dclk->width, CLK_DIVIDER_ROUND_CLOSEST);
}