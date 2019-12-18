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
typedef  unsigned long u32 ;
struct TYPE_2__ {scalar_t__ divider_reg; } ;
struct xgene_clk {TYPE_1__ param; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct xgene_clk* to_xgene_clk (struct clk_hw*) ; 

__attribute__((used)) static long xgene_clk_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	struct xgene_clk *pclk = to_xgene_clk(hw);
	unsigned long parent_rate = *prate;
	u32 divider;

	if (pclk->param.divider_reg) {
		/* Let's compute the divider */
		if (rate > parent_rate)
			rate = parent_rate;
		divider = parent_rate / rate;   /* Rounded down */
	} else {
		divider = 1;
	}

	return parent_rate / divider;
}