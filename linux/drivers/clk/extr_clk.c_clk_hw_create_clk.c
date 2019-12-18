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
struct clk_hw {struct clk_core* core; } ;
struct clk_core {int /*<<< orphan*/  ref; int /*<<< orphan*/  owner; } ;
struct clk {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_CAST (struct clk_hw*) ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct clk_hw*) ; 
 struct clk* alloc_clk (struct clk_core*,char const*,char const*) ; 
 int /*<<< orphan*/  clk_core_link_consumer (struct clk_core*,struct clk*) ; 
 int /*<<< orphan*/  free_clk (struct clk*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct clk *clk_hw_create_clk(struct device *dev, struct clk_hw *hw,
			      const char *dev_id, const char *con_id)
{
	struct clk *clk;
	struct clk_core *core;

	/* This is to allow this function to be chained to others */
	if (IS_ERR_OR_NULL(hw))
		return ERR_CAST(hw);

	core = hw->core;
	clk = alloc_clk(core, dev_id, con_id);
	if (IS_ERR(clk))
		return clk;
	clk->dev = dev;

	if (!try_module_get(core->owner)) {
		free_clk(clk);
		return ERR_PTR(-ENOENT);
	}

	kref_get(&core->ref);
	clk_core_link_consumer(core, clk);

	return clk;
}