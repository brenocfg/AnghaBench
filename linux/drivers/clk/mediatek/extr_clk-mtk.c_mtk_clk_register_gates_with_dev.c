#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct mtk_gate {size_t id; struct device_node* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  ops; int /*<<< orphan*/  shift; TYPE_1__* regs; int /*<<< orphan*/  parent_name; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct clk_onecell_data {struct regmap** clks; } ;
typedef  struct regmap clk ;
struct TYPE_2__ {int /*<<< orphan*/  sta_ofs; int /*<<< orphan*/  clr_ofs; int /*<<< orphan*/  set_ofs; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* mtk_clk_register_gate (struct device_node*,int /*<<< orphan*/ ,struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,int) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

int mtk_clk_register_gates_with_dev(struct device_node *node,
		const struct mtk_gate *clks,
		int num, struct clk_onecell_data *clk_data,
		struct device *dev)
{
	int i;
	struct clk *clk;
	struct regmap *regmap;

	if (!clk_data)
		return -ENOMEM;

	regmap = syscon_node_to_regmap(node);
	if (IS_ERR(regmap)) {
		pr_err("Cannot find regmap for %pOF: %ld\n", node,
				PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	for (i = 0; i < num; i++) {
		const struct mtk_gate *gate = &clks[i];

		if (!IS_ERR_OR_NULL(clk_data->clks[gate->id]))
			continue;

		clk = mtk_clk_register_gate(gate->name, gate->parent_name,
				regmap,
				gate->regs->set_ofs,
				gate->regs->clr_ofs,
				gate->regs->sta_ofs,
				gate->shift, gate->ops, gate->flags, dev);

		if (IS_ERR(clk)) {
			pr_err("Failed to register clk %s: %ld\n",
					gate->name, PTR_ERR(clk));
			continue;
		}

		clk_data->clks[gate->id] = clk;
	}

	return 0;
}