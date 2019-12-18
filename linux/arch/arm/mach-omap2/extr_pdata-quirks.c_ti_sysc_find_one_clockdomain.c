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
struct clockdomain {int dummy; } ;
struct clk_hw_omap {scalar_t__ clkdm_name; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_get_hw (struct clk*) ; 
 struct clockdomain* clkdm_lookup (scalar_t__) ; 
 struct clk_hw_omap* to_clk_hw_omap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clockdomain *ti_sysc_find_one_clockdomain(struct clk *clk)
{
	struct clockdomain *clkdm = NULL;
	struct clk_hw_omap *hwclk;

	hwclk = to_clk_hw_omap(__clk_get_hw(clk));
	if (hwclk && hwclk->clkdm_name)
		clkdm = clkdm_lookup(hwclk->clkdm_name);

	return clkdm;
}