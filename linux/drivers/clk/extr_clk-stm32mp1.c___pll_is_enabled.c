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
struct stm32_pll_obj {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL_ON ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct stm32_pll_obj* to_pll (struct clk_hw*) ; 

__attribute__((used)) static int __pll_is_enabled(struct clk_hw *hw)
{
	struct stm32_pll_obj *clk_elem = to_pll(hw);

	return readl_relaxed(clk_elem->reg) & PLL_ON;
}