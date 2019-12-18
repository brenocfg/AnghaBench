#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_8__ {int clk_num; struct clk** clks; } ;
struct TYPE_9__ {TYPE_1__ clk_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk*) ; 
 TYPE_2__* clk_crgctrl_data ; 
 int /*<<< orphan*/  hi3660_clk_crgctrl_early_init (struct device_node*) ; 
 int /*<<< orphan*/  hi3660_crg_fixed_factor_clks ; 
 int /*<<< orphan*/  hi3660_crgctrl_divider_clks ; 
 int /*<<< orphan*/  hi3660_crgctrl_gate_clks ; 
 int /*<<< orphan*/  hi3660_crgctrl_gate_sep_clks ; 
 int /*<<< orphan*/  hi3660_crgctrl_mux_clks ; 
 int /*<<< orphan*/  hisi_clk_register_divider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hisi_clk_register_fixed_factor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hisi_clk_register_gate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hisi_clk_register_gate_sep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hisi_clk_register_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hi3660_clk_crgctrl_init(struct device_node *np)
{
	struct clk **clks;
	int i;

	if (!clk_crgctrl_data)
		hi3660_clk_crgctrl_early_init(np);

	/* clk_crgctrl_data initialization failed */
	if (!clk_crgctrl_data)
		return;

	hisi_clk_register_gate_sep(hi3660_crgctrl_gate_sep_clks,
				   ARRAY_SIZE(hi3660_crgctrl_gate_sep_clks),
				   clk_crgctrl_data);
	hisi_clk_register_gate(hi3660_crgctrl_gate_clks,
			       ARRAY_SIZE(hi3660_crgctrl_gate_clks),
			       clk_crgctrl_data);
	hisi_clk_register_mux(hi3660_crgctrl_mux_clks,
			      ARRAY_SIZE(hi3660_crgctrl_mux_clks),
			      clk_crgctrl_data);
	hisi_clk_register_fixed_factor(hi3660_crg_fixed_factor_clks,
				       ARRAY_SIZE(hi3660_crg_fixed_factor_clks),
				       clk_crgctrl_data);
	hisi_clk_register_divider(hi3660_crgctrl_divider_clks,
				  ARRAY_SIZE(hi3660_crgctrl_divider_clks),
				  clk_crgctrl_data);

	clks = clk_crgctrl_data->clk_data.clks;
	for (i = 0; i < clk_crgctrl_data->clk_data.clk_num; i++) {
		if (IS_ERR(clks[i]) && PTR_ERR(clks[i]) != -EPROBE_DEFER)
			pr_err("Failed to register crgctrl clock[%d] err=%ld\n",
			       i, PTR_ERR(clks[i]));
	}
}