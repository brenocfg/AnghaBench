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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;
struct aspeed_clk_gate {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  map; int /*<<< orphan*/  clock_idx; } ;

/* Variables and functions */
 int CLK_GATE_SET_TO_DISABLE ; 
 int /*<<< orphan*/  get_bit (int /*<<< orphan*/ ) ; 
 scalar_t__ get_clock_reg (struct aspeed_clk_gate*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct aspeed_clk_gate* to_aspeed_clk_gate (struct clk_hw*) ; 

__attribute__((used)) static void aspeed_g6_clk_disable(struct clk_hw *hw)
{
	struct aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	unsigned long flags;
	u32 clk = get_bit(gate->clock_idx);

	spin_lock_irqsave(gate->lock, flags);

	if (gate->flags & CLK_GATE_SET_TO_DISABLE) {
		regmap_write(gate->map, get_clock_reg(gate), clk);
	} else {
		/* Use set to clear register */
		regmap_write(gate->map, get_clock_reg(gate) + 0x4, clk);
	}

	spin_unlock_irqrestore(gate->lock, flags);
}