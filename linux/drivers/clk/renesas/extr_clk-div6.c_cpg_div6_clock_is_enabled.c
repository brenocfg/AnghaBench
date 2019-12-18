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
struct div6_clock {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CPG_DIV6_CKSTP ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct div6_clock* to_div6_clock (struct clk_hw*) ; 

__attribute__((used)) static int cpg_div6_clock_is_enabled(struct clk_hw *hw)
{
	struct div6_clock *clock = to_div6_clock(hw);

	return !(readl(clock->reg) & CPG_DIV6_CKSTP);
}