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
struct clk_pllv3 {int /*<<< orphan*/  base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BM_PLL_LOCK ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pllv3* to_clk_pllv3 (struct clk_hw*) ; 

__attribute__((used)) static int clk_pllv3_is_prepared(struct clk_hw *hw)
{
	struct clk_pllv3 *pll = to_clk_pllv3(hw);

	if (readl_relaxed(pll->base) & BM_PLL_LOCK)
		return 1;

	return 0;
}