#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {scalar_t__* clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int CLK_INFRA_NR ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_2__* infra_clk_data ; 
 int /*<<< orphan*/  infra_clks ; 
 int /*<<< orphan*/  infra_fixed_divs ; 
 TYPE_2__* mtk_alloc_clk_data (int) ; 
 int /*<<< orphan*/  mtk_clk_register_factors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mtk_clk_register_gates (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 

__attribute__((used)) static int mtk_infrasys_init(struct platform_device *pdev)
{
	int r, i;
	struct device_node *node = pdev->dev.of_node;

	if (!infra_clk_data) {
		infra_clk_data = mtk_alloc_clk_data(CLK_INFRA_NR);
	} else {
		for (i = 0; i < CLK_INFRA_NR; i++) {
			if (infra_clk_data->clks[i] == ERR_PTR(-EPROBE_DEFER))
				infra_clk_data->clks[i] = ERR_PTR(-ENOENT);
		}
	}

	mtk_clk_register_gates(node, infra_clks, ARRAY_SIZE(infra_clks),
			       infra_clk_data);
	mtk_clk_register_factors(infra_fixed_divs, ARRAY_SIZE(infra_fixed_divs),
				 infra_clk_data);

	r = of_clk_add_provider(node, of_clk_src_onecell_get, infra_clk_data);
	if (r)
		return r;

	return 0;
}