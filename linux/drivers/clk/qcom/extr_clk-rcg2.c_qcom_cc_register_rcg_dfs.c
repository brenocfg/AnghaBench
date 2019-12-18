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
struct clk_rcg_dfs_data {int dummy; } ;

/* Variables and functions */
 int clk_rcg2_enable_dfs (struct clk_rcg_dfs_data const*,struct regmap*) ; 

int qcom_cc_register_rcg_dfs(struct regmap *regmap,
			     const struct clk_rcg_dfs_data *rcgs, size_t len)
{
	int i, ret;

	for (i = 0; i < len; i++) {
		ret = clk_rcg2_enable_dfs(&rcgs[i], regmap);
		if (ret)
			return ret;
	}

	return 0;
}