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
struct clk_hw {int dummy; } ;
struct clk_gate2 {int /*<<< orphan*/  bit_idx; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int clk_gate2_reg_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_gate2* to_clk_gate2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_gate2_is_enabled(struct clk_hw *hw)
{
	struct clk_gate2 *gate = to_clk_gate2(hw);

	return clk_gate2_reg_is_enabled(gate->reg, gate->bit_idx);
}