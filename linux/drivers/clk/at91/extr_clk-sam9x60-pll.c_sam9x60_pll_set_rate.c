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
struct sam9x60_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int sam9x60_pll_get_best_div_mul (struct sam9x60_pll*,unsigned long,unsigned long,int) ; 
 struct sam9x60_pll* to_sam9x60_pll (struct clk_hw*) ; 

__attribute__((used)) static int sam9x60_pll_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct sam9x60_pll *pll = to_sam9x60_pll(hw);

	return sam9x60_pll_get_best_div_mul(pll, rate, parent_rate, true);
}