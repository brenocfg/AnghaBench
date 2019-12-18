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
struct hfpll_data {unsigned long max_rate; int /*<<< orphan*/  min_rate; } ;
struct clk_hw {int dummy; } ;
struct clk_hfpll {struct hfpll_data* d; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 unsigned long clamp (unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_hfpll* to_clk_hfpll (struct clk_hw*) ; 

__attribute__((used)) static long clk_hfpll_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *parent_rate)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	unsigned long rrate;

	rate = clamp(rate, hd->min_rate, hd->max_rate);

	rrate = DIV_ROUND_UP(rate, *parent_rate) * *parent_rate;
	if (rrate > hd->max_rate)
		rrate -= *parent_rate;

	return rrate;
}