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
struct mtk_gate {int dummy; } ;
struct device_node {int dummy; } ;
struct clk_onecell_data {int dummy; } ;

/* Variables and functions */
 int mtk_clk_register_gates_with_dev (struct device_node*,struct mtk_gate const*,int,struct clk_onecell_data*,int /*<<< orphan*/ *) ; 

int mtk_clk_register_gates(struct device_node *node,
		const struct mtk_gate *clks,
		int num, struct clk_onecell_data *clk_data)
{
	return mtk_clk_register_gates_with_dev(node,
		clks, num, clk_data, NULL);
}