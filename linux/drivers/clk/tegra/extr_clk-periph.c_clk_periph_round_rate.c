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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {struct clk_hw hw; } ;
struct tegra_clk_periph {TYPE_1__ divider; struct clk_ops* div_ops; } ;
struct clk_ops {long (* round_rate ) (struct clk_hw*,unsigned long,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 long stub1 (struct clk_hw*,unsigned long,unsigned long*) ; 
 struct tegra_clk_periph* to_clk_periph (struct clk_hw*) ; 

__attribute__((used)) static long clk_periph_round_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long *prate)
{
	struct tegra_clk_periph *periph = to_clk_periph(hw);
	const struct clk_ops *div_ops = periph->div_ops;
	struct clk_hw *div_hw = &periph->divider.hw;

	__clk_hw_set_clk(div_hw, hw);

	return div_ops->round_rate(div_hw, rate, prate);
}