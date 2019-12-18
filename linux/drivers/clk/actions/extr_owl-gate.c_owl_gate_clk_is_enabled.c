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
struct owl_gate_hw {int gate_flags; int /*<<< orphan*/  bit_idx; int /*<<< orphan*/  reg; } ;
struct owl_clk_common {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CLK_GATE_SET_TO_DISABLE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int owl_gate_clk_is_enabled(const struct owl_clk_common *common,
		   const struct owl_gate_hw *gate_hw)
{
	u32 reg;

	regmap_read(common->regmap, gate_hw->reg, &reg);

	if (gate_hw->gate_flags & CLK_GATE_SET_TO_DISABLE)
		reg ^= BIT(gate_hw->bit_idx);

	return !!(reg & BIT(gate_hw->bit_idx));
}