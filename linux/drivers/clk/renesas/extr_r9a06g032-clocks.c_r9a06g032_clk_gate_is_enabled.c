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
struct TYPE_2__ {scalar_t__ gate; scalar_t__ reset; } ;
struct r9a06g032_clk_gate {TYPE_1__ gate; int /*<<< orphan*/  clocks; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_rdesc_get (int /*<<< orphan*/ ,scalar_t__) ; 
 struct r9a06g032_clk_gate* to_r9a06g032_gate (struct clk_hw*) ; 

__attribute__((used)) static int r9a06g032_clk_gate_is_enabled(struct clk_hw *hw)
{
	struct r9a06g032_clk_gate *g = to_r9a06g032_gate(hw);

	/* if clock is in reset, the gate might be on, and still not 'be' on */
	if (g->gate.reset && !clk_rdesc_get(g->clocks, g->gate.reset))
		return 0;

	return clk_rdesc_get(g->clocks, g->gate.gate);
}