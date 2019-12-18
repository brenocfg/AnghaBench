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
struct stm32f4_pll {scalar_t__ offset; } ;
struct clk_hw {int dummy; } ;
struct clk_gate {int dummy; } ;

/* Variables and functions */
 scalar_t__ base ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stm32f4_pll_disable (struct clk_hw*) ; 
 int /*<<< orphan*/  stm32f4_pll_enable (struct clk_hw*) ; 
 int stm32f4_pll_is_enabled (struct clk_hw*) ; 
 struct clk_gate* to_clk_gate (struct clk_hw*) ; 
 struct stm32f4_pll* to_stm32f4_pll (struct clk_gate*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int stm32f4_pll_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct clk_gate *gate = to_clk_gate(hw);
	struct stm32f4_pll *pll = to_stm32f4_pll(gate);

	unsigned long n;
	unsigned long val;
	int pll_state;

	pll_state = stm32f4_pll_is_enabled(hw);

	if (pll_state)
		stm32f4_pll_disable(hw);

	n = rate  / parent_rate;

	val = readl(base + pll->offset) & ~(0x1ff << 6);

	writel(val | ((n & 0x1ff) <<  6), base + pll->offset);

	if (pll_state)
		stm32f4_pll_enable(hw);

	return 0;
}