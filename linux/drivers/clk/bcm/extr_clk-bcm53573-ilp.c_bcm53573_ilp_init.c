#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_node {int /*<<< orphan*/  name; } ;
struct clk_init_data {char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct clk_init_data* init; } ;
struct bcm53573_ilp {TYPE_1__ hw; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm53573_ilp_clk_ops ; 
 int clk_hw_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  clk_hw_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct bcm53573_ilp*) ; 
 struct bcm53573_ilp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_clk_add_hw_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* of_clk_get_parent_name (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 int /*<<< orphan*/  of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm53573_ilp_init(struct device_node *np)
{
	struct bcm53573_ilp *ilp;
	struct clk_init_data init = { };
	const char *parent_name;
	int err;

	ilp = kzalloc(sizeof(*ilp), GFP_KERNEL);
	if (!ilp)
		return;

	parent_name = of_clk_get_parent_name(np, 0);
	if (!parent_name) {
		err = -ENOENT;
		goto err_free_ilp;
	}

	ilp->regmap = syscon_node_to_regmap(of_get_parent(np));
	if (IS_ERR(ilp->regmap)) {
		err = PTR_ERR(ilp->regmap);
		goto err_free_ilp;
	}

	init.name = np->name;
	init.ops = &bcm53573_ilp_clk_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	ilp->hw.init = &init;
	err = clk_hw_register(NULL, &ilp->hw);
	if (err)
		goto err_free_ilp;

	err = of_clk_add_hw_provider(np, of_clk_hw_simple_get, &ilp->hw);
	if (err)
		goto err_clk_hw_unregister;

	return;

err_clk_hw_unregister:
	clk_hw_unregister(&ilp->hw);
err_free_ilp:
	kfree(ilp);
	pr_err("Failed to init ILP clock: %d\n", err);
}