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
struct sam9x60_pll {int mul; int div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct sam9x60_pll* to_sam9x60_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long sam9x60_pll_recalc_rate(struct clk_hw *hw,
					     unsigned long parent_rate)
{
	struct sam9x60_pll *pll = to_sam9x60_pll(hw);

	return (parent_rate * (pll->mul + 1)) / (pll->div + 1);
}