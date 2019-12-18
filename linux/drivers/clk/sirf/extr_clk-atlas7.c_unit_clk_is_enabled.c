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
typedef  scalar_t__ u32 ;
struct clk_unit {int /*<<< orphan*/  bit; scalar_t__ regofs; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SIRFSOC_CLKC_ROOT_CLK_EN0_SET ; 
 scalar_t__ SIRFSOC_CLKC_ROOT_CLK_EN0_STAT ; 
 int clkc_readl (scalar_t__) ; 
 struct clk_unit* to_unitclk (struct clk_hw*) ; 

__attribute__((used)) static int unit_clk_is_enabled(struct clk_hw *hw)
{
	struct clk_unit *clk = to_unitclk(hw);
	u32 reg;

	reg = clk->regofs + SIRFSOC_CLKC_ROOT_CLK_EN0_STAT - SIRFSOC_CLKC_ROOT_CLK_EN0_SET;

	return !!(clkc_readl(reg) & BIT(clk->bit));
}