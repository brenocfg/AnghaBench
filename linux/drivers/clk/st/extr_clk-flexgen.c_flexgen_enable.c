#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct TYPE_5__ {struct clk_hw hw; } ;
struct TYPE_4__ {struct clk_hw hw; } ;
struct flexgen {TYPE_2__ fgate; TYPE_1__ pgate; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* enable ) (struct clk_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 TYPE_3__ clk_gate_ops ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clk_hw*) ; 
 int /*<<< orphan*/  stub2 (struct clk_hw*) ; 
 struct flexgen* to_flexgen (struct clk_hw*) ; 

__attribute__((used)) static int flexgen_enable(struct clk_hw *hw)
{
	struct flexgen *flexgen = to_flexgen(hw);
	struct clk_hw *pgate_hw = &flexgen->pgate.hw;
	struct clk_hw *fgate_hw = &flexgen->fgate.hw;

	__clk_hw_set_clk(pgate_hw, hw);
	__clk_hw_set_clk(fgate_hw, hw);

	clk_gate_ops.enable(pgate_hw);

	clk_gate_ops.enable(fgate_hw);

	pr_debug("%s: flexgen output enabled\n", clk_hw_get_name(hw));
	return 0;
}