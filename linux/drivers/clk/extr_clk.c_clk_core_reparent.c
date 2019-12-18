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
struct clk_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POST_RATE_CHANGE ; 
 int /*<<< orphan*/  __clk_recalc_accuracies (struct clk_core*) ; 
 int /*<<< orphan*/  __clk_recalc_rates (struct clk_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_reparent (struct clk_core*,struct clk_core*) ; 

__attribute__((used)) static void clk_core_reparent(struct clk_core *core,
				  struct clk_core *new_parent)
{
	clk_reparent(core, new_parent);
	__clk_recalc_accuracies(core);
	__clk_recalc_rates(core, POST_RATE_CHANGE);
}