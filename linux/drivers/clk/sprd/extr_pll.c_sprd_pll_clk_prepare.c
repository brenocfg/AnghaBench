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
struct sprd_pll {int /*<<< orphan*/  udelay; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct sprd_pll* hw_to_sprd_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_pll_clk_prepare(struct clk_hw *hw)
{
	struct sprd_pll *pll = hw_to_sprd_pll(hw);

	udelay(pll->udelay);

	return 0;
}