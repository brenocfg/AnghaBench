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
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct generic_pm_domain {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 struct clk* of_clk_get_from_provider (struct of_phandle_args*) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_node_name_eq (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 int pm_clk_add_clk (struct device*,struct clk*) ; 
 int pm_clk_create (struct device*) ; 
 int /*<<< orphan*/  pm_clk_destroy (struct device*) ; 

int cpg_mstp_attach_dev(struct generic_pm_domain *unused, struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct of_phandle_args clkspec;
	struct clk *clk;
	int i = 0;
	int error;

	while (!of_parse_phandle_with_args(np, "clocks", "#clock-cells", i,
					   &clkspec)) {
		if (of_device_is_compatible(clkspec.np,
					    "renesas,cpg-mstp-clocks"))
			goto found;

		/* BSC on r8a73a4/sh73a0 uses zb_clk instead of an mstp clock */
		if (of_node_name_eq(clkspec.np, "zb_clk"))
			goto found;

		of_node_put(clkspec.np);
		i++;
	}

	return 0;

found:
	clk = of_clk_get_from_provider(&clkspec);
	of_node_put(clkspec.np);

	if (IS_ERR(clk))
		return PTR_ERR(clk);

	error = pm_clk_create(dev);
	if (error)
		goto fail_put;

	error = pm_clk_add_clk(dev, clk);
	if (error)
		goto fail_destroy;

	return 0;

fail_destroy:
	pm_clk_destroy(dev);
fail_put:
	clk_put(clk);
	return error;
}