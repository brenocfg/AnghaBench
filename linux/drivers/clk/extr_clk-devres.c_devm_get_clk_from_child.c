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
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  devm_clk_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct clk**) ; 
 struct clk** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct clk**) ; 
 struct clk* of_clk_get_by_name (struct device_node*,char const*) ; 

struct clk *devm_get_clk_from_child(struct device *dev,
				    struct device_node *np, const char *con_id)
{
	struct clk **ptr, *clk;

	ptr = devres_alloc(devm_clk_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	clk = of_clk_get_by_name(np, con_id);
	if (!IS_ERR(clk)) {
		*ptr = clk;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return clk;
}