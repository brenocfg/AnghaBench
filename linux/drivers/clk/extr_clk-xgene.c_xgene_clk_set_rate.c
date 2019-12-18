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
typedef  int u32 ;
struct TYPE_2__ {int reg_divider_width; int reg_divider_shift; scalar_t__ reg_divider_offset; scalar_t__ divider_reg; } ;
struct xgene_clk {scalar_t__ lock; TYPE_1__ param; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct xgene_clk* to_xgene_clk (struct clk_hw*) ; 
 int xgene_clk_read (scalar_t__) ; 
 int /*<<< orphan*/  xgene_clk_write (int,scalar_t__) ; 

__attribute__((used)) static int xgene_clk_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct xgene_clk *pclk = to_xgene_clk(hw);
	unsigned long flags = 0;
	u32 data;
	u32 divider;
	u32 divider_save;

	if (pclk->lock)
		spin_lock_irqsave(pclk->lock, flags);

	if (pclk->param.divider_reg) {
		/* Let's compute the divider */
		if (rate > parent_rate)
			rate = parent_rate;
		divider_save = divider = parent_rate / rate; /* Rounded down */
		divider &= (1 << pclk->param.reg_divider_width) - 1;
		divider <<= pclk->param.reg_divider_shift;

		/* Set new divider */
		data = xgene_clk_read(pclk->param.divider_reg +
				pclk->param.reg_divider_offset);
		data &= ~(((1 << pclk->param.reg_divider_width) - 1)
				<< pclk->param.reg_divider_shift);
		data |= divider;
		xgene_clk_write(data, pclk->param.divider_reg +
					pclk->param.reg_divider_offset);
		pr_debug("%s clock set rate %ld\n", clk_hw_get_name(hw),
			parent_rate / divider_save);
	} else {
		divider_save = 1;
	}

	if (pclk->lock)
		spin_unlock_irqrestore(pclk->lock, flags);

	return parent_rate / divider_save;
}