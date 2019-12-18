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
struct r9a06g032_clk_gate {int /*<<< orphan*/  gate; int /*<<< orphan*/  clocks; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r9a06g032_clk_gate_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct r9a06g032_clk_gate* to_r9a06g032_gate (struct clk_hw*) ; 

__attribute__((used)) static int r9a06g032_clk_gate_enable(struct clk_hw *hw)
{
	struct r9a06g032_clk_gate *g = to_r9a06g032_gate(hw);

	r9a06g032_clk_gate_set(g->clocks, &g->gate, 1);
	return 0;
}