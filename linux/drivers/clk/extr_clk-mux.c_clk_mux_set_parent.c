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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct clk_mux {int flags; int mask; int shift; scalar_t__ lock; int /*<<< orphan*/  table; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_MUX_HIWORD_MASK ; 
 int /*<<< orphan*/  __acquire (scalar_t__) ; 
 int /*<<< orphan*/  __release (scalar_t__) ; 
 int clk_mux_index_to_val (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int clk_mux_readl (struct clk_mux*) ; 
 int /*<<< orphan*/  clk_mux_writel (struct clk_mux*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_mux* to_clk_mux (struct clk_hw*) ; 

__attribute__((used)) static int clk_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_mux *mux = to_clk_mux(hw);
	u32 val = clk_mux_index_to_val(mux->table, mux->flags, index);
	unsigned long flags = 0;
	u32 reg;

	if (mux->lock)
		spin_lock_irqsave(mux->lock, flags);
	else
		__acquire(mux->lock);

	if (mux->flags & CLK_MUX_HIWORD_MASK) {
		reg = mux->mask << (mux->shift + 16);
	} else {
		reg = clk_mux_readl(mux);
		reg &= ~(mux->mask << mux->shift);
	}
	val = val << mux->shift;
	reg |= val;
	clk_mux_writel(mux, reg);

	if (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);
	else
		__release(mux->lock);

	return 0;
}