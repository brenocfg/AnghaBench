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
struct aspeed_clk_gate {scalar_t__ clock_idx; scalar_t__ reset_idx; long flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_CLK_STOP_CTRL ; 
 int /*<<< orphan*/  ASPEED_RESET_CTRL ; 
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 long CLK_GATE_SET_TO_DISABLE ; 
 scalar_t__ aspeed_clk_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct aspeed_clk_gate* to_aspeed_clk_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int aspeed_clk_enable(struct clk_hw *hw)
{
	struct aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	unsigned long flags;
	u32 clk = BIT(gate->clock_idx);
	u32 rst = BIT(gate->reset_idx);
	u32 enval;

	spin_lock_irqsave(gate->lock, flags);

	if (aspeed_clk_is_enabled(hw)) {
		spin_unlock_irqrestore(gate->lock, flags);
		return 0;
	}

	if (gate->reset_idx >= 0) {
		/* Put IP in reset */
		regmap_update_bits(gate->map, ASPEED_RESET_CTRL, rst, rst);

		/* Delay 100us */
		udelay(100);
	}

	/* Enable clock */
	enval = (gate->flags & CLK_GATE_SET_TO_DISABLE) ? 0 : clk;
	regmap_update_bits(gate->map, ASPEED_CLK_STOP_CTRL, clk, enval);

	if (gate->reset_idx >= 0) {
		/* A delay of 10ms is specified by the ASPEED docs */
		mdelay(10);

		/* Take IP out of reset */
		regmap_update_bits(gate->map, ASPEED_RESET_CTRL, rst, 0);
	}

	spin_unlock_irqrestore(gate->lock, flags);

	return 0;
}