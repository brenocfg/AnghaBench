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
struct owl_clk_desc {int num_clks; struct owl_clk_common** clks; } ;
struct owl_clk_common {struct regmap* regmap; } ;

/* Variables and functions */

__attribute__((used)) static void owl_clk_set_regmap(const struct owl_clk_desc *desc,
			 struct regmap *regmap)
{
	int i;
	struct owl_clk_common *clks;

	for (i = 0; i < desc->num_clks; i++) {
		clks = desc->clks[i];
		if (!clks)
			continue;

		clks->regmap = regmap;
	}
}