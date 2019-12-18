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
struct uniphier_clk_gate {int /*<<< orphan*/  bit; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uniphier_clk_gate* to_uniphier_clk_gate (struct clk_hw*) ; 

__attribute__((used)) static int uniphier_clk_gate_endisable(struct clk_hw *hw, int enable)
{
	struct uniphier_clk_gate *gate = to_uniphier_clk_gate(hw);

	return regmap_write_bits(gate->regmap, gate->reg, BIT(gate->bit),
				 enable ? BIT(gate->bit) : 0);
}