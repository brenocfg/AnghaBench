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
struct m10v_clk_divider {int flags; int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  table; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_DIVIDER_READ_ONLY ; 
 int clk_div_mask (int /*<<< orphan*/ ) ; 
 long divider_ro_round_rate (struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 long divider_round_rate (struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct m10v_clk_divider* to_m10v_div (struct clk_hw*) ; 

__attribute__((used)) static long m10v_clk_divider_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	struct m10v_clk_divider *divider = to_m10v_div(hw);

	/* if read only, just return current value */
	if (divider->flags & CLK_DIVIDER_READ_ONLY) {
		u32 val;

		val = readl(divider->reg) >> divider->shift;
		val &= clk_div_mask(divider->width);

		return divider_ro_round_rate(hw, rate, prate, divider->table,
					     divider->width, divider->flags,
					     val);
	}

	return divider_round_rate(hw, rate, prate, divider->table,
				  divider->width, divider->flags);
}