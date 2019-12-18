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
struct clk_hw {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 struct clk* clk_register (struct device*,struct clk_hw*) ; 
 int /*<<< orphan*/  devm_clk_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct clk**) ; 
 struct clk** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct clk**) ; 

struct clk *devm_clk_register(struct device *dev, struct clk_hw *hw)
{
	struct clk *clk;
	struct clk **clkp;

	clkp = devres_alloc(devm_clk_release, sizeof(*clkp), GFP_KERNEL);
	if (!clkp)
		return ERR_PTR(-ENOMEM);

	clk = clk_register(dev, hw);
	if (!IS_ERR(clk)) {
		*clkp = clk;
		devres_add(dev, clkp);
	} else {
		devres_free(clkp);
	}

	return clk;
}