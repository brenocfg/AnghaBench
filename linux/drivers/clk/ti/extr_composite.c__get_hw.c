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
struct clk_hw_omap_comp {TYPE_1__** comp_clks; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {struct clk_hw* hw; } ;

/* Variables and functions */

__attribute__((used)) static inline struct clk_hw *_get_hw(struct clk_hw_omap_comp *clk, int idx)
{
	if (!clk)
		return NULL;

	if (!clk->comp_clks[idx])
		return NULL;

	return clk->comp_clks[idx]->hw;
}