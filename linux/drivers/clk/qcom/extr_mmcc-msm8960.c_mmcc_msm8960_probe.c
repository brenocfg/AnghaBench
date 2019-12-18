#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * init; } ;
struct TYPE_6__ {TYPE_1__ hw; } ;
struct TYPE_8__ {TYPE_3__* s; TYPE_2__ clkr; int /*<<< orphan*/  freq_tbl; } ;
struct TYPE_7__ {void* parent_map; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_pll_configure_sr (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clk_tbl_gfx3d_8064 ; 
 int /*<<< orphan*/  gfx3d_8064_init ; 
 TYPE_4__ gfx3d_src ; 
 int /*<<< orphan*/  mmcc_msm8960_match_table ; 
 void* mmcc_pxo_pll8_pll2_pll15_map ; 
 int of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  pll15 ; 
 int /*<<< orphan*/  pll15_config ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ ) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ ,struct regmap*) ; 

__attribute__((used)) static int mmcc_msm8960_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct regmap *regmap;
	bool is_8064;
	struct device *dev = &pdev->dev;

	match = of_match_device(mmcc_msm8960_match_table, dev);
	if (!match)
		return -EINVAL;

	is_8064 = of_device_is_compatible(dev->of_node, "qcom,mmcc-apq8064");
	if (is_8064) {
		gfx3d_src.freq_tbl = clk_tbl_gfx3d_8064;
		gfx3d_src.clkr.hw.init = &gfx3d_8064_init;
		gfx3d_src.s[0].parent_map = mmcc_pxo_pll8_pll2_pll15_map;
		gfx3d_src.s[1].parent_map = mmcc_pxo_pll8_pll2_pll15_map;
	}

	regmap = qcom_cc_map(pdev, match->data);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	clk_pll_configure_sr(&pll15, regmap, &pll15_config, false);

	return qcom_cc_really_probe(pdev, match->data, regmap);
}