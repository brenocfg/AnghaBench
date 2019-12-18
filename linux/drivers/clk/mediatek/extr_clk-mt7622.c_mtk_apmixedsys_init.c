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
struct clk_onecell_data {int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t CLK_APMIXED_ARMPLL ; 
 size_t CLK_APMIXED_MAIN_CORE_EN ; 
 int /*<<< orphan*/  CLK_APMIXED_NR_CLK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  apmixed_clks ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct clk_onecell_data* mtk_alloc_clk_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_clk_register_gates (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int /*<<< orphan*/  mtk_clk_register_plls (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 
 int /*<<< orphan*/  plls ; 

__attribute__((used)) static int mtk_apmixedsys_init(struct platform_device *pdev)
{
	struct clk_onecell_data *clk_data;
	struct device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_APMIXED_NR_CLK);
	if (!clk_data)
		return -ENOMEM;

	mtk_clk_register_plls(node, plls, ARRAY_SIZE(plls),
			      clk_data);

	mtk_clk_register_gates(node, apmixed_clks,
			       ARRAY_SIZE(apmixed_clks), clk_data);

	clk_prepare_enable(clk_data->clks[CLK_APMIXED_ARMPLL]);
	clk_prepare_enable(clk_data->clks[CLK_APMIXED_MAIN_CORE_EN]);

	return of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
}