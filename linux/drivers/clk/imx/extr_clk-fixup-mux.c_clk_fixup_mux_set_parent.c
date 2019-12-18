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
typedef  int u8 ;
typedef  int u32 ;
struct clk_mux {int mask; int shift; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;
struct clk_fixup_mux {int /*<<< orphan*/  (* fixup ) (int*) ;} ;

/* Variables and functions */
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 struct clk_fixup_mux* to_clk_fixup_mux (struct clk_hw*) ; 
 struct clk_mux* to_clk_mux (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_fixup_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_fixup_mux *fixup_mux = to_clk_fixup_mux(hw);
	struct clk_mux *mux = to_clk_mux(hw);
	unsigned long flags = 0;
	u32 val;

	spin_lock_irqsave(mux->lock, flags);

	val = readl(mux->reg);
	val &= ~(mux->mask << mux->shift);
	val |= index << mux->shift;
	fixup_mux->fixup(&val);
	writel(val, mux->reg);

	spin_unlock_irqrestore(mux->lock, flags);

	return 0;
}