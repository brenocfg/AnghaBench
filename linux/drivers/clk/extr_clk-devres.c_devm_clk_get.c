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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 struct clk* clk_get (struct device*,char const*) ; 
 int /*<<< orphan*/  devm_clk_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct clk**) ; 
 struct clk** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct clk**) ; 

struct clk *devm_clk_get(struct device *dev, const char *id)
{
	struct clk **ptr, *clk;

	ptr = devres_alloc(devm_clk_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	clk = clk_get(dev, id);
	if (!IS_ERR(clk)) {
		*ptr = clk;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return clk;
}