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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct clk_onecell_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_INFRA_NR_CLK ; 
 int /*<<< orphan*/  infra_clks ; 
 int /*<<< orphan*/  infra_muxes ; 
 struct clk_onecell_data* mtk_alloc_clk_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_clk_register_cpumuxes (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int /*<<< orphan*/  mtk_clk_register_gates (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 

__attribute__((used)) static int mtk_infrasys_init(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct clk_onecell_data *clk_data;
	int r;

	clk_data = mtk_alloc_clk_data(CLK_INFRA_NR_CLK);

	mtk_clk_register_gates(node, infra_clks, ARRAY_SIZE(infra_clks),
			       clk_data);

	mtk_clk_register_cpumuxes(node, infra_muxes, ARRAY_SIZE(infra_muxes),
				  clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get,
				clk_data);
	if (r)
		return r;

	return 0;
}