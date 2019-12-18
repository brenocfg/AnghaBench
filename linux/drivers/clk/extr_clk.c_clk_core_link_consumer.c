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
struct clk_core {int /*<<< orphan*/  clks; } ;
struct clk {int /*<<< orphan*/  clks_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clk_core_link_consumer(struct clk_core *core, struct clk *clk)
{
	clk_prepare_lock();
	hlist_add_head(&clk->clks_node, &core->clks);
	clk_prepare_unlock();
}