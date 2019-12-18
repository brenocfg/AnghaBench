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
struct device {int dummy; } ;
struct clk_lookup {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_clkdev_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct clk_lookup**) ; 
 struct clk_lookup** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct clk_lookup**) ; 
 int do_clk_register_clkdev (struct clk_hw*,struct clk_lookup**,char const*,char const*) ; 

int devm_clk_hw_register_clkdev(struct device *dev, struct clk_hw *hw,
				const char *con_id, const char *dev_id)
{
	int rval = -ENOMEM;
	struct clk_lookup **cl;

	cl = devres_alloc(devm_clkdev_release, sizeof(*cl), GFP_KERNEL);
	if (cl) {
		rval = do_clk_register_clkdev(hw, cl, con_id, dev_id);
		if (!rval)
			devres_add(dev, cl);
		else
			devres_free(cl);
	}
	return rval;
}