#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;
struct clk_alpha_pll {int num_vco; TYPE_1__* vco_table; } ;
struct TYPE_2__ {unsigned long min_freq; unsigned long max_freq; } ;

/* Variables and functions */
 scalar_t__ alpha_pll_find_vco (struct clk_alpha_pll*,unsigned long) ; 
 unsigned long alpha_pll_round_rate (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long clamp (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pll_alpha_width (struct clk_alpha_pll*) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 

__attribute__((used)) static long clk_alpha_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, alpha_width = pll_alpha_width(pll);
	u64 a;
	unsigned long min_freq, max_freq;

	rate = alpha_pll_round_rate(rate, *prate, &l, &a, alpha_width);
	if (!pll->vco_table || alpha_pll_find_vco(pll, rate))
		return rate;

	min_freq = pll->vco_table[0].min_freq;
	max_freq = pll->vco_table[pll->num_vco - 1].max_freq;

	return clamp(rate, min_freq, max_freq);
}