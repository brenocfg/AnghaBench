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
struct omap_device {TYPE_1__* pdev; } ;
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int clk_add_alias (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 struct clk* clk_get_sys (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int clk_register_clkdev (struct clk*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * dev_name (int /*<<< orphan*/ *) ; 
 struct clk* of_clk_get_from_provider (struct of_phandle_args*) ; 
 int /*<<< orphan*/  of_find_node_by_name (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void _add_clkdev(struct omap_device *od, const char *clk_alias,
		       const char *clk_name)
{
	struct clk *r;
	int rc;

	if (!clk_alias || !clk_name)
		return;

	dev_dbg(&od->pdev->dev, "Creating %s -> %s\n", clk_alias, clk_name);

	r = clk_get_sys(dev_name(&od->pdev->dev), clk_alias);
	if (!IS_ERR(r)) {
		dev_dbg(&od->pdev->dev,
			 "alias %s already exists\n", clk_alias);
		clk_put(r);
		return;
	}

	r = clk_get_sys(NULL, clk_name);

	if (IS_ERR(r)) {
		struct of_phandle_args clkspec;

		clkspec.np = of_find_node_by_name(NULL, clk_name);

		r = of_clk_get_from_provider(&clkspec);

		rc = clk_register_clkdev(r, clk_alias,
					 dev_name(&od->pdev->dev));
	} else {
		rc = clk_add_alias(clk_alias, dev_name(&od->pdev->dev),
				   clk_name, NULL);
	}

	if (rc) {
		if (rc == -ENODEV || rc == -ENOMEM)
			dev_err(&od->pdev->dev,
				"clkdev_alloc for %s failed\n", clk_alias);
		else
			dev_err(&od->pdev->dev,
				"clk_get for %s failed\n", clk_name);
	}
}