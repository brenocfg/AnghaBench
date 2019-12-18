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
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  mmcc_msm8996_desc ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ *,struct regmap*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmcc_msm8996_probe(struct platform_device *pdev)
{
	struct regmap *regmap;

	regmap = qcom_cc_map(pdev, &mmcc_msm8996_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/* Disable the AHB DCD */
	regmap_update_bits(regmap, 0x50d8, BIT(31), 0);
	/* Disable the NoC FSM for mmss_mmagic_cfg_ahb_clk */
	regmap_update_bits(regmap, 0x5054, BIT(15), 0);

	return qcom_cc_really_probe(pdev, &mmcc_msm8996_desc, regmap);
}