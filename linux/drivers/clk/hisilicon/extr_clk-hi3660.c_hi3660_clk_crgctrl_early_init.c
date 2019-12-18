#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * clks; } ;
struct TYPE_6__ {TYPE_1__ clk_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_2__* clk_crgctrl_data ; 
 int /*<<< orphan*/  hi3660_crg_fixed_factor_clks ; 
 int /*<<< orphan*/  hi3660_crgctrl_divider_clks ; 
 int /*<<< orphan*/  hi3660_crgctrl_gate_clks ; 
 int /*<<< orphan*/  hi3660_crgctrl_gate_sep_clks ; 
 int /*<<< orphan*/  hi3660_crgctrl_mux_clks ; 
 int /*<<< orphan*/  hi3660_fixed_rate_clks ; 
 TYPE_2__* hisi_clk_init (struct device_node*,int) ; 
 int /*<<< orphan*/  hisi_clk_register_fixed_rate (int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static void hi3660_clk_crgctrl_early_init(struct device_node *np)
{
	int nr = ARRAY_SIZE(hi3660_fixed_rate_clks) +
		 ARRAY_SIZE(hi3660_crgctrl_gate_sep_clks) +
		 ARRAY_SIZE(hi3660_crgctrl_gate_clks) +
		 ARRAY_SIZE(hi3660_crgctrl_mux_clks) +
		 ARRAY_SIZE(hi3660_crg_fixed_factor_clks) +
		 ARRAY_SIZE(hi3660_crgctrl_divider_clks);
	int i;

	clk_crgctrl_data = hisi_clk_init(np, nr);
	if (!clk_crgctrl_data)
		return;

	for (i = 0; i < nr; i++)
		clk_crgctrl_data->clk_data.clks[i] = ERR_PTR(-EPROBE_DEFER);

	hisi_clk_register_fixed_rate(hi3660_fixed_rate_clks,
				     ARRAY_SIZE(hi3660_fixed_rate_clks),
				     clk_crgctrl_data);
}