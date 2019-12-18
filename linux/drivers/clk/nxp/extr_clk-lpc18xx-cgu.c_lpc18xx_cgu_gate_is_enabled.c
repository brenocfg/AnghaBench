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
struct TYPE_2__ {int (* is_enabled ) (struct clk_hw*) ;} ;

/* Variables and functions */
 TYPE_1__ clk_gate_ops ; 
 struct clk_hw* clk_hw_get_parent (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_hw_is_enabled (struct clk_hw const*) ; 
 int stub1 (struct clk_hw*) ; 

__attribute__((used)) static int lpc18xx_cgu_gate_is_enabled(struct clk_hw *hw)
{
	const struct clk_hw *parent;

	/*
	 * The consumer of base clocks needs know if the
	 * base clock is really enabled before it can be
	 * accessed. It is therefore necessary to verify
	 * this all the way up.
	 */
	parent = clk_hw_get_parent(hw);
	if (!parent)
		return 0;

	if (!clk_hw_is_enabled(parent))
		return 0;

	return clk_gate_ops.is_enabled(hw);
}