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
typedef  unsigned long u32 ;
struct davinci_pll_clk {unsigned long pllm_min; unsigned long pllm_max; } ;
struct clk_rate_request {unsigned long best_parent_rate; unsigned long rate; unsigned long min_rate; unsigned long max_rate; struct clk_hw* best_parent_hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_SET_RATE_PARENT ; 
 int EINVAL ; 
 int clk_hw_get_flags (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (struct clk_hw*,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 struct davinci_pll_clk* to_davinci_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static int davinci_pll_determine_rate(struct clk_hw *hw,
				      struct clk_rate_request *req)
{
	struct davinci_pll_clk *pll = to_davinci_pll_clk(hw);
	struct clk_hw *parent = req->best_parent_hw;
	unsigned long parent_rate = req->best_parent_rate;
	unsigned long rate = req->rate;
	unsigned long best_rate, r;
	u32 mult;

	/* there is a limited range of valid outputs (see datasheet) */
	if (rate < req->min_rate)
		return -EINVAL;

	rate = min(rate, req->max_rate);
	mult = rate / parent_rate;
	best_rate = parent_rate * mult;

	/* easy case when there is no PREDIV */
	if (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) {
		if (best_rate < req->min_rate)
			return -EINVAL;

		if (mult < pll->pllm_min || mult > pll->pllm_max)
			return -EINVAL;

		req->rate = best_rate;

		return 0;
	}

	/* see if the PREDIV clock can help us */
	best_rate = 0;

	for (mult = pll->pllm_min; mult <= pll->pllm_max; mult++) {
		parent_rate = clk_hw_round_rate(parent, rate / mult);
		r = parent_rate * mult;
		if (r < req->min_rate)
			continue;
		if (r > rate || r > req->max_rate)
			break;
		if (r > best_rate) {
			best_rate = r;
			req->rate = best_rate;
			req->best_parent_rate = parent_rate;
			if (best_rate == rate)
				break;
		}
	}

	return 0;
}