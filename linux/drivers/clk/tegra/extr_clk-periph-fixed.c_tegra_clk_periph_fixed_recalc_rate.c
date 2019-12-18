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
struct tegra_clk_periph_fixed {unsigned long long mul; int /*<<< orphan*/  div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 struct tegra_clk_periph_fixed* to_tegra_clk_periph_fixed (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
tegra_clk_periph_fixed_recalc_rate(struct clk_hw *hw,
				   unsigned long parent_rate)
{
	struct tegra_clk_periph_fixed *fixed = to_tegra_clk_periph_fixed(hw);
	unsigned long long rate;

	rate = (unsigned long long)parent_rate * fixed->mul;
	do_div(rate, fixed->div);

	return (unsigned long)rate;
}