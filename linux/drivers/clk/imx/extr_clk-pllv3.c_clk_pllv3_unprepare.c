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
struct clk_pllv3 {int /*<<< orphan*/  base; int /*<<< orphan*/  power_bit; scalar_t__ powerup_set; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pllv3* to_clk_pllv3 (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_pllv3_unprepare(struct clk_hw *hw)
{
	struct clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 val;

	val = readl_relaxed(pll->base);
	if (pll->powerup_set)
		val &= ~pll->power_bit;
	else
		val |= pll->power_bit;
	writel_relaxed(val, pll->base);
}