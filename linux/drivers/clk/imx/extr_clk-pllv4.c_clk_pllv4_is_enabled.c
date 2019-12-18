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
struct clk_pllv4 {int /*<<< orphan*/  base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL_EN ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pllv4* to_clk_pllv4 (struct clk_hw*) ; 

__attribute__((used)) static int clk_pllv4_is_enabled(struct clk_hw *hw)
{
	struct clk_pllv4 *pll = to_clk_pllv4(hw);

	if (readl_relaxed(pll->base) & PLL_EN)
		return 1;

	return 0;
}