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
struct omap_hwmod {scalar_t__ _clk; struct clockdomain* clkdm; } ;
struct clockdomain {int dummy; } ;
struct clk_hw_omap {struct clockdomain* clkdm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_get_hw (scalar_t__) ; 
 int /*<<< orphan*/  omap2_clk_is_hw_omap (int /*<<< orphan*/ ) ; 
 struct clk_hw_omap* to_clk_hw_omap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clockdomain *_get_clkdm(struct omap_hwmod *oh)
{
	struct clk_hw_omap *clk;

	if (oh->clkdm) {
		return oh->clkdm;
	} else if (oh->_clk) {
		if (!omap2_clk_is_hw_omap(__clk_get_hw(oh->_clk)))
			return NULL;
		clk = to_clk_hw_omap(__clk_get_hw(oh->_clk));
		return clk->clkdm;
	}
	return NULL;
}