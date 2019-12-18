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
struct uniphier_clk_cpugear_data {int /*<<< orphan*/  mask; int /*<<< orphan*/  regbase; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; } ;
struct clk_hw {struct clk_init_data* init; } ;
struct uniphier_clk_cpugear {struct clk_hw hw; int /*<<< orphan*/  mask; int /*<<< orphan*/  regbase; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct clk_init_data {char const* name; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int devm_clk_hw_register (struct device*,struct clk_hw*) ; 
 struct uniphier_clk_cpugear* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_clk_cpugear_ops ; 

struct clk_hw *uniphier_clk_register_cpugear(struct device *dev,
					 struct regmap *regmap,
					 const char *name,
				const struct uniphier_clk_cpugear_data *data)
{
	struct uniphier_clk_cpugear *gear;
	struct clk_init_data init;
	int ret;

	gear = devm_kzalloc(dev, sizeof(*gear), GFP_KERNEL);
	if (!gear)
		return ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &uniphier_clk_cpugear_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = data->parent_names;
	init.num_parents = data->num_parents,

	gear->regmap = regmap;
	gear->regbase = data->regbase;
	gear->mask = data->mask;
	gear->hw.init = &init;

	ret = devm_clk_hw_register(dev, &gear->hw);
	if (ret)
		return ERR_PTR(ret);

	return &gear->hw;
}