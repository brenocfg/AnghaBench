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
struct sprd_clk_desc {int num_clk_clks; struct sprd_clk_common** clk_clks; } ;
struct sprd_clk_common {struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void sprd_clk_set_regmap(const struct sprd_clk_desc *desc,
			 struct regmap *regmap)
{
	int i;
	struct sprd_clk_common *cclk;

	for (i = 0; i < desc->num_clk_clks; i++) {
		cclk = desc->clk_clks[i];
		if (!cclk)
			continue;

		cclk->regmap = regmap;
	}
}