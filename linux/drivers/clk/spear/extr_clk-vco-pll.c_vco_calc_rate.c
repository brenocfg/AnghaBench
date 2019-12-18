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
struct clk_vco {int /*<<< orphan*/  rtbl; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long pll_calc_rate (int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ *) ; 
 struct clk_vco* to_clk_vco (struct clk_hw*) ; 

__attribute__((used)) static inline unsigned long vco_calc_rate(struct clk_hw *hw,
		unsigned long prate, int index)
{
	struct clk_vco *vco = to_clk_vco(hw);

	return pll_calc_rate(vco->rtbl, prate, index, NULL);
}