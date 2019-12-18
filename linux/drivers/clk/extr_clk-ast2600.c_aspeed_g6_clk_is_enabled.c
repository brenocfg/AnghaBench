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
struct clk_hw {int dummy; } ;
struct aspeed_clk_gate {scalar_t__ clock_idx; scalar_t__ reset_idx; int flags; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int CLK_GATE_SET_TO_DISABLE ; 
 int get_bit (scalar_t__) ; 
 int /*<<< orphan*/  get_clock_reg (struct aspeed_clk_gate*) ; 
 int /*<<< orphan*/  get_reset_reg (struct aspeed_clk_gate*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct aspeed_clk_gate* to_aspeed_clk_gate (struct clk_hw*) ; 

__attribute__((used)) static int aspeed_g6_clk_is_enabled(struct clk_hw *hw)
{
	struct aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	u32 clk = get_bit(gate->clock_idx);
	u32 rst = get_bit(gate->reset_idx);
	u32 reg;
	u32 enval;

	/*
	 * If the IP is in reset, treat the clock as not enabled,
	 * this happens with some clocks such as the USB one when
	 * coming from cold reset. Without this, aspeed_clk_enable()
	 * will fail to lift the reset.
	 */
	if (gate->reset_idx >= 0) {
		regmap_read(gate->map, get_reset_reg(gate), &reg);

		if (reg & rst)
			return 0;
	}

	regmap_read(gate->map, get_clock_reg(gate), &reg);

	enval = (gate->flags & CLK_GATE_SET_TO_DISABLE) ? 0 : clk;

	return ((reg & clk) == enval) ? 1 : 0;
}