#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysc {TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct clk_lookup {char const* con_id; struct clk* clk; int /*<<< orphan*/  dev_id; } ;
struct clk {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clkdev_add (struct clk_lookup*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 struct clk* devm_get_clk_from_child (TYPE_1__*,struct device_node*,char const*) ; 
 struct clk_lookup* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct clk* of_clk_get_by_name (struct device_node*,char const*) ; 
 struct device_node* of_get_next_available_child (struct device_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sysc_add_named_clock_from_child(struct sysc *ddata,
					   const char *name,
					   const char *optfck_name)
{
	struct device_node *np = ddata->dev->of_node;
	struct device_node *child;
	struct clk_lookup *cl;
	struct clk *clock;
	const char *n;

	if (name)
		n = name;
	else
		n = optfck_name;

	/* Does the clock alias already exist? */
	clock = of_clk_get_by_name(np, n);
	if (!IS_ERR(clock)) {
		clk_put(clock);

		return 0;
	}

	child = of_get_next_available_child(np, NULL);
	if (!child)
		return -ENODEV;

	clock = devm_get_clk_from_child(ddata->dev, child, name);
	if (IS_ERR(clock))
		return PTR_ERR(clock);

	/*
	 * Use clkdev_add() instead of clkdev_alloc() to avoid the MAX_DEV_ID
	 * limit for clk_get(). If cl ever needs to be freed, it should be done
	 * with clkdev_drop().
	 */
	cl = kcalloc(1, sizeof(*cl), GFP_KERNEL);
	if (!cl)
		return -ENOMEM;

	cl->con_id = n;
	cl->dev_id = dev_name(ddata->dev);
	cl->clk = clock;
	clkdev_add(cl);

	clk_put(clock);

	return 0;
}