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
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct clk_dmn {int /*<<< orphan*/  regofs; } ;

/* Variables and functions */
 int BIT (int) ; 
 int clkc_readl (int /*<<< orphan*/ ) ; 
 struct clk_dmn* to_dmnclk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long dmn_clk_recalc_rate(struct clk_hw *hw,
	unsigned long parent_rate)

{
	unsigned long fin = parent_rate;
	struct clk_dmn *clk = to_dmnclk(hw);

	u32 cfg = clkc_readl(clk->regofs);

	if (cfg & BIT(24)) {
		/* fcd bypass mode */
		return fin;
	} else {
		/*
		 * wait count: bit[19:16], hold count: bit[23:20]
		 */
		u32 wait = (cfg >> 16) & (BIT(4) - 1);
		u32 hold = (cfg >> 20) & (BIT(4) - 1);

		return fin / (wait + hold + 2);
	}
}