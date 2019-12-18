#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stm32f4_pll {int /*<<< orphan*/  bit_rdy_idx; } ;
struct clk_hw {int dummy; } ;
struct clk_gate {int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct clk_hw*) ;scalar_t__ (* is_enabled ) (struct clk_hw*) ;} ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 unsigned int PLL_TIMEOUT ; 
 TYPE_1__ clk_gate_ops ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct clk_hw*) ; 
 int /*<<< orphan*/  stub2 (struct clk_hw*) ; 
 struct clk_gate* to_clk_gate (struct clk_hw*) ; 
 struct stm32f4_pll* to_stm32f4_pll (struct clk_gate*) ; 

__attribute__((used)) static int stm32f4_pll_enable(struct clk_hw *hw)
{
	struct clk_gate *gate = to_clk_gate(hw);
	struct stm32f4_pll *pll = to_stm32f4_pll(gate);
	int bit_status;
	unsigned int timeout = PLL_TIMEOUT;

	if (clk_gate_ops.is_enabled(hw))
		return 0;

	clk_gate_ops.enable(hw);

	do {
		bit_status = !(readl(gate->reg) & BIT(pll->bit_rdy_idx));

	} while (bit_status && --timeout);

	return bit_status;
}