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
struct mtk_mux {size_t id; struct device_node* name; } ;
struct device_node {int dummy; } ;
struct clk_onecell_data {struct regmap** clks; } ;
typedef  struct regmap clk ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* mtk_clk_register_mux (struct mtk_mux const*,struct regmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,int) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

int mtk_clk_register_muxes(const struct mtk_mux *muxes,
			   int num, struct device_node *node,
			   spinlock_t *lock,
			   struct clk_onecell_data *clk_data)
{
	struct regmap *regmap;
	struct clk *clk;
	int i;

	regmap = syscon_node_to_regmap(node);
	if (IS_ERR(regmap)) {
		pr_err("Cannot find regmap for %pOF: %ld\n", node,
		       PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	for (i = 0; i < num; i++) {
		const struct mtk_mux *mux = &muxes[i];

		if (IS_ERR_OR_NULL(clk_data->clks[mux->id])) {
			clk = mtk_clk_register_mux(mux, regmap, lock);

			if (IS_ERR(clk)) {
				pr_err("Failed to register clk %s: %ld\n",
				       mux->name, PTR_ERR(clk));
				continue;
			}

			clk_data->clks[mux->id] = clk;
		}
	}

	return 0;
}