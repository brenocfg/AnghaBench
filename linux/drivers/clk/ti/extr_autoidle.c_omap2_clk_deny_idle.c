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
struct clk_hw_omap {int dummy; } ;
struct clk_hw {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct clk_hw* __clk_get_hw (struct clk*) ; 
 int _omap2_clk_deny_idle (struct clk_hw_omap*) ; 
 scalar_t__ omap2_clk_is_hw_omap (struct clk_hw*) ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

int omap2_clk_deny_idle(struct clk *clk)
{
	struct clk_hw *hw = __clk_get_hw(clk);

	if (omap2_clk_is_hw_omap(hw)) {
		struct clk_hw_omap *c = to_clk_hw_omap(hw);

		return _omap2_clk_deny_idle(c);
	}

	return -EINVAL;
}