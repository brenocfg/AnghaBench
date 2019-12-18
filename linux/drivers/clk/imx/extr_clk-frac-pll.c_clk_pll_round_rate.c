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
typedef  int u64 ;
typedef  int u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL_FRAC_DENOM ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static long clk_pll_round_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long *prate)
{
	u64 parent_rate = *prate;
	u32 divff, divfi;
	u64 temp64;

	parent_rate *= 8;
	rate *= 2;
	temp64 = rate;
	do_div(temp64, parent_rate);
	divfi = temp64;
	temp64 = rate - divfi * parent_rate;
	temp64 *= PLL_FRAC_DENOM;
	do_div(temp64, parent_rate);
	divff = temp64;

	temp64 = parent_rate;
	temp64 *= divff;
	do_div(temp64, PLL_FRAC_DENOM);

	rate = parent_rate * divfi + temp64;

	return rate / 2;
}