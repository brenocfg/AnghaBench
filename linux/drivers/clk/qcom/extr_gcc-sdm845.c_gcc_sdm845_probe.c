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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  gcc_dfs_clocks ; 
 int /*<<< orphan*/  gcc_sdm845_desc ; 
 struct regmap* qcom_cc_map (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_really_probe (struct platform_device*,int /*<<< orphan*/ *,struct regmap*) ; 
 int qcom_cc_register_rcg_dfs (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int,int,int) ; 

__attribute__((used)) static int gcc_sdm845_probe(struct platform_device *pdev)
{
	struct regmap *regmap;
	int ret;

	regmap = qcom_cc_map(pdev, &gcc_sdm845_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/* Disable the GPLL0 active input to MMSS and GPU via MISC registers */
	regmap_update_bits(regmap, 0x09ffc, 0x3, 0x3);
	regmap_update_bits(regmap, 0x71028, 0x3, 0x3);

	ret = qcom_cc_register_rcg_dfs(regmap, gcc_dfs_clocks,
					ARRAY_SIZE(gcc_dfs_clocks));
	if (ret)
		return ret;

	return qcom_cc_really_probe(pdev, &gcc_sdm845_desc, regmap);
}