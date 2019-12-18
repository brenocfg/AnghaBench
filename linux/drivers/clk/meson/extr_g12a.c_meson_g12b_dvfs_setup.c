#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk_hw {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  hw; } ;
struct TYPE_19__ {int /*<<< orphan*/  nb; } ;
struct TYPE_18__ {int /*<<< orphan*/  hw; } ;
struct TYPE_17__ {int /*<<< orphan*/  hw; } ;
struct TYPE_16__ {int /*<<< orphan*/  hw; } ;
struct TYPE_15__ {int /*<<< orphan*/  nb; struct clk_hw* xtal; } ;
struct TYPE_14__ {int /*<<< orphan*/  nb; } ;
struct TYPE_13__ {struct clk_hw** hws; } ;
struct TYPE_12__ {int /*<<< orphan*/  hw; } ;
struct TYPE_11__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 size_t CLKID_CPU_CLK_DYN1_SEL ; 
 struct clk* __clk_lookup (char const*) ; 
 char* clk_hw_get_name (int /*<<< orphan*/ *) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int /*<<< orphan*/ ) ; 
 int clk_notifier_register (struct clk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g12a_cpu_clk_mux_nb ; 
 TYPE_10__ g12a_sys_pll ; 
 TYPE_9__ g12b_cpu_clk ; 
 TYPE_8__ g12b_cpu_clk_sys1_pll_nb_data ; 
 TYPE_7__ g12b_cpub_clk ; 
 TYPE_6__ g12b_cpub_clk_dyn ; 
 TYPE_5__ g12b_cpub_clk_postmux0 ; 
 TYPE_4__ g12b_cpub_clk_postmux0_nb_data ; 
 TYPE_3__ g12b_cpub_clk_sys_pll_nb_data ; 
 TYPE_2__ g12b_hw_onecell_data ; 
 TYPE_1__ g12b_sys1_pll ; 
 int meson_g12a_dvfs_setup_common (struct platform_device*,struct clk_hw**) ; 

__attribute__((used)) static int meson_g12b_dvfs_setup(struct platform_device *pdev)
{
	struct clk_hw **hws = g12b_hw_onecell_data.hws;
	const char *notifier_clk_name;
	struct clk *notifier_clk;
	struct clk_hw *xtal;
	int ret;

	ret = meson_g12a_dvfs_setup_common(pdev, hws);
	if (ret)
		return ret;

	xtal = clk_hw_get_parent_by_index(hws[CLKID_CPU_CLK_DYN1_SEL], 0);

	/* Setup clock notifier for cpu_clk mux */
	notifier_clk_name = clk_hw_get_name(&g12b_cpu_clk.hw);
	notifier_clk = __clk_lookup(notifier_clk_name);
	ret = clk_notifier_register(notifier_clk, &g12a_cpu_clk_mux_nb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register the cpu_clk notifier\n");
		return ret;
	}

	/* Setup clock notifier for sys1_pll */
	notifier_clk_name = clk_hw_get_name(&g12b_sys1_pll.hw);
	notifier_clk = __clk_lookup(notifier_clk_name);
	ret = clk_notifier_register(notifier_clk,
				    &g12b_cpu_clk_sys1_pll_nb_data.nb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register the sys1_pll notifier\n");
		return ret;
	}

	/* Add notifiers for the second CPU cluster */

	/* Setup clock notifier for cpub_clk_postmux0 */
	g12b_cpub_clk_postmux0_nb_data.xtal = xtal;
	notifier_clk_name = clk_hw_get_name(&g12b_cpub_clk_postmux0.hw);
	notifier_clk = __clk_lookup(notifier_clk_name);
	ret = clk_notifier_register(notifier_clk,
				    &g12b_cpub_clk_postmux0_nb_data.nb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register the cpub_clk_postmux0 notifier\n");
		return ret;
	}

	/* Setup clock notifier for cpub_clk_dyn mux */
	notifier_clk_name = clk_hw_get_name(&g12b_cpub_clk_dyn.hw);
	notifier_clk = __clk_lookup(notifier_clk_name);
	ret = clk_notifier_register(notifier_clk, &g12a_cpu_clk_mux_nb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register the cpub_clk_dyn notifier\n");
		return ret;
	}

	/* Setup clock notifier for cpub_clk mux */
	notifier_clk_name = clk_hw_get_name(&g12b_cpub_clk.hw);
	notifier_clk = __clk_lookup(notifier_clk_name);
	ret = clk_notifier_register(notifier_clk, &g12a_cpu_clk_mux_nb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register the cpub_clk notifier\n");
		return ret;
	}

	/* Setup clock notifier for sys_pll */
	notifier_clk_name = clk_hw_get_name(&g12a_sys_pll.hw);
	notifier_clk = __clk_lookup(notifier_clk_name);
	ret = clk_notifier_register(notifier_clk,
				    &g12b_cpub_clk_sys_pll_nb_data.nb);
	if (ret) {
		dev_err(&pdev->dev, "failed to register the sys_pll notifier\n");
		return ret;
	}

	return 0;
}