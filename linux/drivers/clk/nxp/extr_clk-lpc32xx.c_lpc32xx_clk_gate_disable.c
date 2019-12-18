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
struct lpc32xx_clk_gate {int flags; int /*<<< orphan*/  reg; int /*<<< orphan*/  bit_idx; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CLK_GATE_SET_TO_DISABLE ; 
 int /*<<< orphan*/  clk_regmap ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct lpc32xx_clk_gate* to_lpc32xx_gate (struct clk_hw*) ; 

__attribute__((used)) static void lpc32xx_clk_gate_disable(struct clk_hw *hw)
{
	struct lpc32xx_clk_gate *clk = to_lpc32xx_gate(hw);
	u32 mask = BIT(clk->bit_idx);
	u32 val = (clk->flags & CLK_GATE_SET_TO_DISABLE ? mask : 0x0);

	regmap_update_bits(clk_regmap, clk->reg, mask, val);
}