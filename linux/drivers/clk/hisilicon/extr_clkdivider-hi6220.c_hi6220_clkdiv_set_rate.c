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
struct hi6220_clk_divider {int shift; int mask; scalar_t__ lock; int /*<<< orphan*/  reg; int /*<<< orphan*/  width; int /*<<< orphan*/  table; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_DIVIDER_ROUND_CLOSEST ; 
 int div_mask (int /*<<< orphan*/ ) ; 
 int divider_get_val (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct hi6220_clk_divider* to_hi6220_clk_divider (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi6220_clkdiv_set_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long parent_rate)
{
	int value;
	unsigned long flags = 0;
	u32 data;
	struct hi6220_clk_divider *dclk = to_hi6220_clk_divider(hw);

	value = divider_get_val(rate, parent_rate, dclk->table,
				dclk->width, CLK_DIVIDER_ROUND_CLOSEST);

	if (dclk->lock)
		spin_lock_irqsave(dclk->lock, flags);

	data = readl_relaxed(dclk->reg);
	data &= ~(div_mask(dclk->width) << dclk->shift);
	data |= value << dclk->shift;
	data |= dclk->mask;

	writel_relaxed(data, dclk->reg);

	if (dclk->lock)
		spin_unlock_irqrestore(dclk->lock, flags);

	return 0;
}