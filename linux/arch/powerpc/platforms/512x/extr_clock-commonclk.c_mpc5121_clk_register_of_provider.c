#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_3__ {scalar_t__ clk_num; int /*<<< orphan*/  clks; } ;

/* Variables and functions */
 scalar_t__ MPC512x_CLK_LAST_PUBLIC ; 
 TYPE_1__ clk_data ; 
 int /*<<< orphan*/  clks ; 
 int /*<<< orphan*/  of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 

__attribute__((used)) static void mpc5121_clk_register_of_provider(struct device_node *np)
{
	clk_data.clks = clks;
	clk_data.clk_num = MPC512x_CLK_LAST_PUBLIC + 1;	/* _not_ ARRAY_SIZE() */
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data);
}