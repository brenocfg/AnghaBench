#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct regmap {int dummy; } ;
struct platform_device {int dummy; } ;
struct alpha_pll_config {int l; int alpha; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_fabia_pll_configure (int /*<<< orphan*/ *,struct regmap*,struct alpha_pll_config*) ; 
 int /*<<< orphan*/  disp_cc_pll0 ; 
 int /*<<< orphan*/  disp_cc_sdm845_desc ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ *,struct regmap*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int,int,int) ; 

__attribute__((used)) static int disp_cc_sdm845_probe(struct platform_device *pdev)
{
	struct regmap *regmap;
	struct alpha_pll_config disp_cc_pll0_config = {};

	regmap = qcom_cc_map(pdev, &disp_cc_sdm845_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	disp_cc_pll0_config.l = 0x2c;
	disp_cc_pll0_config.alpha = 0xcaaa;

	clk_fabia_pll_configure(&disp_cc_pll0, regmap, &disp_cc_pll0_config);

	/* Enable hardware clock gating for DSI and MDP clocks */
	regmap_update_bits(regmap, 0x8000, 0x7f0, 0x7f0);

	return qcom_cc_really_probe(pdev, &disp_cc_sdm845_desc, regmap);
}