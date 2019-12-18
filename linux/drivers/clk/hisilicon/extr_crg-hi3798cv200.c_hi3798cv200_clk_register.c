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
 int /*<<< orphan*/  HI3798CV200_CRG_NR_CLKS ; 
 int /*<<< orphan*/  hi3798cv200_fixed_rate_clks ; 
 int /*<<< orphan*/  hi3798cv200_gate_clks ; 
 int /*<<< orphan*/  hi3798cv200_mux_clks ; 
 int /*<<< orphan*/  hi3798cv200_phase_clks ; 
 struct hisi_clock_data* hisi_clk_alloc (struct platform_device*,int /*<<< orphan*/ ) ; 
 int hisi_clk_register_fixed_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int hisi_clk_register_gate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int hisi_clk_register_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int hisi_clk_register_phase (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int /*<<< orphan*/  hisi_clk_unregister_fixed_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int /*<<< orphan*/  hisi_clk_unregister_gate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int /*<<< orphan*/  hisi_clk_unregister_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hisi_clock_data*) ; 
 int of_clk_add_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 

__attribute__((used)) static struct hisi_clock_data *hi3798cv200_clk_register(
				struct platform_device *pdev)
{
	struct hisi_clock_data *clk_data;
	int ret;

	clk_data = hisi_clk_alloc(pdev, HI3798CV200_CRG_NR_CLKS);
	if (!clk_data)
		return ERR_PTR(-ENOMEM);

	/* hisi_phase_clock is resource managed */
	ret = hisi_clk_register_phase(&pdev->dev,
				hi3798cv200_phase_clks,
				ARRAY_SIZE(hi3798cv200_phase_clks),
				clk_data);
	if (ret)
		return ERR_PTR(ret);

	ret = hisi_clk_register_fixed_rate(hi3798cv200_fixed_rate_clks,
				     ARRAY_SIZE(hi3798cv200_fixed_rate_clks),
				     clk_data);
	if (ret)
		return ERR_PTR(ret);

	ret = hisi_clk_register_mux(hi3798cv200_mux_clks,
				ARRAY_SIZE(hi3798cv200_mux_clks),
				clk_data);
	if (ret)
		goto unregister_fixed_rate;

	ret = hisi_clk_register_gate(hi3798cv200_gate_clks,
				ARRAY_SIZE(hi3798cv200_gate_clks),
				clk_data);
	if (ret)
		goto unregister_mux;

	ret = of_clk_add_provider(pdev->dev.of_node,
			of_clk_src_onecell_get, &clk_data->clk_data);
	if (ret)
		goto unregister_gate;

	return clk_data;

unregister_gate:
	hisi_clk_unregister_gate(hi3798cv200_gate_clks,
				ARRAY_SIZE(hi3798cv200_gate_clks),
				clk_data);
unregister_mux:
	hisi_clk_unregister_mux(hi3798cv200_mux_clks,
				ARRAY_SIZE(hi3798cv200_mux_clks),
				clk_data);
unregister_fixed_rate:
	hisi_clk_unregister_fixed_rate(hi3798cv200_fixed_rate_clks,
				ARRAY_SIZE(hi3798cv200_fixed_rate_clks),
				clk_data);
	return ERR_PTR(ret);
}