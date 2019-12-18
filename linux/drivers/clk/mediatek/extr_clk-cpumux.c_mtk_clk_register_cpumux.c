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
struct mtk_composite {int /*<<< orphan*/  mux_width; int /*<<< orphan*/  mux_shift; int /*<<< orphan*/  mux_reg; int /*<<< orphan*/  flags; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct mtk_clk_cpumux {TYPE_1__ hw; struct regmap* regmap; scalar_t__ mask; int /*<<< orphan*/  shift; int /*<<< orphan*/  reg; } ;
struct clk_init_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_cpumux_ops ; 
 struct clk* clk_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct mtk_clk_cpumux*) ; 
 struct mtk_clk_cpumux* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *
mtk_clk_register_cpumux(const struct mtk_composite *mux,
			struct regmap *regmap)
{
	struct mtk_clk_cpumux *cpumux;
	struct clk *clk;
	struct clk_init_data init;

	cpumux = kzalloc(sizeof(*cpumux), GFP_KERNEL);
	if (!cpumux)
		return ERR_PTR(-ENOMEM);

	init.name = mux->name;
	init.ops = &clk_cpumux_ops;
	init.parent_names = mux->parent_names;
	init.num_parents = mux->num_parents;
	init.flags = mux->flags;

	cpumux->reg = mux->mux_reg;
	cpumux->shift = mux->mux_shift;
	cpumux->mask = BIT(mux->mux_width) - 1;
	cpumux->regmap = regmap;
	cpumux->hw.init = &init;

	clk = clk_register(NULL, &cpumux->hw);
	if (IS_ERR(clk))
		kfree(cpumux);

	return clk;
}