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
struct mtk_composite {size_t id; struct device_node* name; } ;
struct device_node {int dummy; } ;
struct clk_onecell_data {struct regmap** clks; } ;
typedef  struct regmap clk ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* mtk_clk_register_cpumux (struct mtk_composite const*,struct regmap*) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,int) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

int mtk_clk_register_cpumuxes(struct device_node *node,
			      const struct mtk_composite *clks, int num,
			      struct clk_onecell_data *clk_data)
{
	int i;
	struct clk *clk;
	struct regmap *regmap;

	regmap = syscon_node_to_regmap(node);
	if (IS_ERR(regmap)) {
		pr_err("Cannot find regmap for %pOF: %ld\n", node,
		       PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	for (i = 0; i < num; i++) {
		const struct mtk_composite *mux = &clks[i];

		clk = mtk_clk_register_cpumux(mux, regmap);
		if (IS_ERR(clk)) {
			pr_err("Failed to register clk %s: %ld\n",
			       mux->name, PTR_ERR(clk));
			continue;
		}

		clk_data->clks[mux->id] = clk;
	}

	return 0;
}