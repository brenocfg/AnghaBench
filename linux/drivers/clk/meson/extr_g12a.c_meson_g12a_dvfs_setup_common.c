#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk_hw {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  nb; struct clk_hw* xtal; } ;

/* Variables and functions */
 size_t CLKID_CPU_CLK_DYN1_SEL ; 
 struct clk* __clk_lookup (char const*) ; 
 char* clk_hw_get_name (int /*<<< orphan*/ *) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int /*<<< orphan*/ ) ; 
 int clk_notifier_register (struct clk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__ g12a_cpu_clk_dyn ; 
 int /*<<< orphan*/  g12a_cpu_clk_mux_nb ; 
 TYPE_2__ g12a_cpu_clk_postmux0 ; 
 TYPE_1__ g12a_cpu_clk_postmux0_nb_data ; 

__attribute__((used)) static int meson_g12a_dvfs_setup_common(struct platform_device *pdev,
					struct clk_hw **hws)
{
	const char *notifier_clk_name;
	struct clk *notifier_clk;
	struct clk_hw *xtal;
	int ret;

	xtal = clk_hw_get_parent_by_index(hws[CLKID_CPU_CLK_DYN1_SEL], 0);

	/* Setup clock notifier for cpu_clk_postmux0 */
	g12a_cpu_clk_postmux0_nb_data.xtal = xtal;
	notifier_clk_name = clk_hw_get_name(&g12a_cpu_clk_postmux0.hw);
	notifier_clk = __clk_lookup(notifier_clk_name);
	ret = clk_notifier_register(notifier_clk,
				    &g12a_cpu_clk_postmux0_nb_data.nb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register the cpu_clk_postmux0 notifier\n");
		return ret;
	}

	/* Setup clock notifier for cpu_clk_dyn mux */
	notifier_clk_name = clk_hw_get_name(&g12a_cpu_clk_dyn.hw);
	notifier_clk = __clk_lookup(notifier_clk_name);
	ret = clk_notifier_register(notifier_clk, &g12a_cpu_clk_mux_nb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register the cpu_clk_dyn notifier\n");
		return ret;
	}

	return 0;
}