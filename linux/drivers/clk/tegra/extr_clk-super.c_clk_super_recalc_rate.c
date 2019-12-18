#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct TYPE_3__ {struct clk_hw hw; } ;
struct tegra_clk_super_mux {TYPE_2__* div_ops; TYPE_1__ frac_div; } ;
struct TYPE_4__ {unsigned long (* recalc_rate ) (struct clk_hw*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 unsigned long stub1 (struct clk_hw*,unsigned long) ; 
 struct tegra_clk_super_mux* to_clk_super_mux (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_super_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct tegra_clk_super_mux *super = to_clk_super_mux(hw);
	struct clk_hw *div_hw = &super->frac_div.hw;

	__clk_hw_set_clk(div_hw, hw);

	return super->div_ops->recalc_rate(div_hw, parent_rate);
}