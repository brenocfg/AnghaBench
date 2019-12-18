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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct clk_omap_reg {int dummy; } ;
struct clk_init_data {char const* name; int num_parents; char const** parent_names; scalar_t__ flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * member_0; } ;
struct clk_hw_omap_ops {int dummy; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clk_hw_omap {TYPE_1__ hw; int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  enable_reg; struct clk_hw_omap_ops const* ops; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  kfree (struct clk_hw_omap*) ; 
 struct clk_hw_omap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct clk_omap_reg*,int) ; 
 struct clk* ti_clk_register_omap_hw (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  ti_interface_clk_ops ; 

__attribute__((used)) static struct clk *_register_interface(struct device *dev, const char *name,
				       const char *parent_name,
				       struct clk_omap_reg *reg, u8 bit_idx,
				       const struct clk_hw_omap_ops *ops)
{
	struct clk_init_data init = { NULL };
	struct clk_hw_omap *clk_hw;
	struct clk *clk;

	clk_hw = kzalloc(sizeof(*clk_hw), GFP_KERNEL);
	if (!clk_hw)
		return ERR_PTR(-ENOMEM);

	clk_hw->hw.init = &init;
	clk_hw->ops = ops;
	memcpy(&clk_hw->enable_reg, reg, sizeof(*reg));
	clk_hw->enable_bit = bit_idx;

	init.name = name;
	init.ops = &ti_interface_clk_ops;
	init.flags = 0;

	init.num_parents = 1;
	init.parent_names = &parent_name;

	clk = ti_clk_register_omap_hw(NULL, &clk_hw->hw, name);

	if (IS_ERR(clk))
		kfree(clk_hw);

	return clk;
}