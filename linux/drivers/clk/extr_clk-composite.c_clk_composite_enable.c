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
struct clk_ops {int (* enable ) (struct clk_hw*) ;} ;
struct clk_hw {int dummy; } ;
struct clk_composite {struct clk_hw* gate_hw; struct clk_ops* gate_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 int stub1 (struct clk_hw*) ; 
 struct clk_composite* to_clk_composite (struct clk_hw*) ; 

__attribute__((used)) static int clk_composite_enable(struct clk_hw *hw)
{
	struct clk_composite *composite = to_clk_composite(hw);
	const struct clk_ops *gate_ops = composite->gate_ops;
	struct clk_hw *gate_hw = composite->gate_hw;

	__clk_hw_set_clk(gate_hw, hw);

	return gate_ops->enable(gate_hw);
}