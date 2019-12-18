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

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_alpha_pll_configure (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_qcs404_desc ; 
 int /*<<< orphan*/  gpll3_config ; 
 int /*<<< orphan*/  gpll3_out_main ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ *,struct regmap*) ; 

__attribute__((used)) static int gcc_qcs404_probe(struct platform_device *pdev)
{
	struct regmap *regmap;

	regmap = qcom_cc_map(pdev, &gcc_qcs404_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	clk_alpha_pll_configure(&gpll3_out_main, regmap, &gpll3_config);

	return qcom_cc_really_probe(pdev, &gcc_qcs404_desc, regmap);
}