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
typedef  int /*<<< orphan*/  u8 ;
struct regmap {int dummy; } ;
struct clk_hw {struct clk_init_data* init; } ;
struct cp110_gate_clk {struct clk_hw hw; int /*<<< orphan*/  bit_idx; struct regmap* regmap; } ;
struct clk_init_data {char const* name; char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; } ;
typedef  int /*<<< orphan*/  init ;

/* Variables and functions */
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int clk_hw_register (int /*<<< orphan*/ *,struct clk_hw*) ; 
 int /*<<< orphan*/  cp110_gate_ops ; 
 int /*<<< orphan*/  kfree (struct cp110_gate_clk*) ; 
 struct cp110_gate_clk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct clk_init_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct clk_hw *cp110_register_gate(const char *name,
					  const char *parent_name,
					  struct regmap *regmap, u8 bit_idx)
{
	struct cp110_gate_clk *gate;
	struct clk_hw *hw;
	struct clk_init_data init;
	int ret;

	gate = kzalloc(sizeof(*gate), GFP_KERNEL);
	if (!gate)
		return ERR_PTR(-ENOMEM);

	memset(&init, 0, sizeof(init));

	init.name = name;
	init.ops = &cp110_gate_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	gate->regmap = regmap;
	gate->bit_idx = bit_idx;
	gate->hw.init = &init;

	hw = &gate->hw;
	ret = clk_hw_register(NULL, hw);
	if (ret) {
		kfree(gate);
		hw = ERR_PTR(ret);
	}

	return hw;
}