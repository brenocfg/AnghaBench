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
typedef  size_t u8 ;
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct clk_hw {struct clk_core* core; } ;
struct clk_core {struct device_node* of_node; struct device* dev; TYPE_1__* parents; } ;
struct TYPE_2__ {char* fw_name; int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clk_core* ERR_CAST (struct clk_hw*) ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct clk_hw*) ; 
 struct clk_hw* clk_find_hw (char const*,char const*) ; 
 char* dev_name (struct device*) ; 
 struct clk_hw* of_clk_get_hw_from_clkspec (struct of_phandle_args*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_parse_clkspec (struct device_node*,int,char const*,struct of_phandle_args*) ; 

__attribute__((used)) static struct clk_core *clk_core_get(struct clk_core *core, u8 p_index)
{
	const char *name = core->parents[p_index].fw_name;
	int index = core->parents[p_index].index;
	struct clk_hw *hw = ERR_PTR(-ENOENT);
	struct device *dev = core->dev;
	const char *dev_id = dev ? dev_name(dev) : NULL;
	struct device_node *np = core->of_node;
	struct of_phandle_args clkspec;

	if (np && (name || index >= 0) &&
	    !of_parse_clkspec(np, index, name, &clkspec)) {
		hw = of_clk_get_hw_from_clkspec(&clkspec);
		of_node_put(clkspec.np);
	} else if (name) {
		/*
		 * If the DT search above couldn't find the provider fallback to
		 * looking up via clkdev based clk_lookups.
		 */
		hw = clk_find_hw(dev_id, name);
	}

	if (IS_ERR(hw))
		return ERR_CAST(hw);

	return hw->core;
}