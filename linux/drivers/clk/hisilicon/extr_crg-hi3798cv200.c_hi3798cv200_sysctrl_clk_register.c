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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hisi_clock_data {int /*<<< orphan*/  clk_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct hisi_clock_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  HI3798CV200_SYSCTRL_NR_CLKS ; 
 int /*<<< orphan*/  hi3798cv200_sysctrl_gate_clks ; 
 struct hisi_clock_data* hisi_clk_alloc (struct platform_device*,int /*<<< orphan*/ ) ; 
 int hisi_clk_register_gate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int /*<<< orphan*/  hisi_clk_unregister_gate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int of_clk_add_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 

__attribute__((used)) static struct hisi_clock_data *hi3798cv200_sysctrl_clk_register(
					struct platform_device *pdev)
{
	struct hisi_clock_data *clk_data;
	int ret;

	clk_data = hisi_clk_alloc(pdev, HI3798CV200_SYSCTRL_NR_CLKS);
	if (!clk_data)
		return ERR_PTR(-ENOMEM);

	ret = hisi_clk_register_gate(hi3798cv200_sysctrl_gate_clks,
				ARRAY_SIZE(hi3798cv200_sysctrl_gate_clks),
				clk_data);
	if (ret)
		return ERR_PTR(ret);

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	if (ret)
		goto unregister_gate;

	return clk_data;

unregister_gate:
	hisi_clk_unregister_gate(hi3798cv200_sysctrl_gate_clks,
				ARRAY_SIZE(hi3798cv200_sysctrl_gate_clks),
				clk_data);
	return ERR_PTR(ret);
}