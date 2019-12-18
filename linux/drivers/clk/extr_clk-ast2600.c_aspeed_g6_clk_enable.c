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
struct aspeed_clk_gate {scalar_t__ clock_idx; scalar_t__ reset_idx; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int CLK_GATE_SET_TO_DISABLE ; 
 scalar_t__ aspeed_g6_clk_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  get_bit (scalar_t__) ; 
 scalar_t__ get_clock_reg (struct aspeed_clk_gate*) ; 
 scalar_t__ get_reset_reg (struct aspeed_clk_gate*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct aspeed_clk_gate* to_aspeed_clk_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int aspeed_g6_clk_enable(struct clk_hw *hw)
{
	struct aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	unsigned long flags;
	u32 clk = get_bit(gate->clock_idx);
	u32 rst = get_bit(gate->reset_idx);

	spin_lock_irqsave(gate->lock, flags);

	if (aspeed_g6_clk_is_enabled(hw)) {
		spin_unlock_irqrestore(gate->lock, flags);
		return 0;
	}

	if (gate->reset_idx >= 0) {
		/* Put IP in reset */
		regmap_write(gate->map, get_reset_reg(gate), rst);
		/* Delay 100us */
		udelay(100);
	}

	/* Enable clock */
	if (gate->flags & CLK_GATE_SET_TO_DISABLE) {
		/* Clock is clear to enable, so use set to clear register */
		regmap_write(gate->map, get_clock_reg(gate) + 0x04, clk);
	} else {
		/* Clock is set to enable, so use write to set register */
		regmap_write(gate->map, get_clock_reg(gate), clk);
	}

	if (gate->reset_idx >= 0) {
		/* A delay of 10ms is specified by the ASPEED docs */
		mdelay(10);
		/* Take IP out of reset */
		regmap_write(gate->map, get_reset_reg(gate) + 0x4, rst);
	}

	spin_unlock_irqrestore(gate->lock, flags);

	return 0;
}