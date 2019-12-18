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
struct of_phandle_args {scalar_t__* args; struct device_node* np; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IMX6QDL_CLK_PLL6 ; 
 scalar_t__ IMX6QDL_PLL6_BYPASS ; 
 int of_count_phandle_with_args (struct device_node*,char*,char*) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 

__attribute__((used)) static bool pll6_bypassed(struct device_node *node)
{
	int index, ret, num_clocks;
	struct of_phandle_args clkspec;

	num_clocks = of_count_phandle_with_args(node, "assigned-clocks",
						"#clock-cells");
	if (num_clocks < 0)
		return false;

	for (index = 0; index < num_clocks; index++) {
		ret = of_parse_phandle_with_args(node, "assigned-clocks",
						 "#clock-cells", index,
						 &clkspec);
		if (ret < 0)
			return false;

		if (clkspec.np == node &&
		    clkspec.args[0] == IMX6QDL_PLL6_BYPASS)
			break;
	}

	/* PLL6 bypass is not part of the assigned clock list */
	if (index == num_clocks)
		return false;

	ret = of_parse_phandle_with_args(node, "assigned-clock-parents",
					 "#clock-cells", index, &clkspec);

	if (clkspec.args[0] != IMX6QDL_CLK_PLL6)
		return true;

	return false;
}