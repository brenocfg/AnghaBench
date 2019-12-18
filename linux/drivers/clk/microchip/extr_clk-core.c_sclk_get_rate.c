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
struct pic32_sys_clk {int /*<<< orphan*/  slew_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int SLEW_SYSDIV ; 
 int SLEW_SYSDIV_SHIFT ; 
 struct pic32_sys_clk* clkhw_to_sys_clk (struct clk_hw*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long sclk_get_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	u32 div;

	div = (readl(sclk->slew_reg) >> SLEW_SYSDIV_SHIFT) & SLEW_SYSDIV;
	div += 1; /* sys-div to divider */

	return parent_rate / div;
}