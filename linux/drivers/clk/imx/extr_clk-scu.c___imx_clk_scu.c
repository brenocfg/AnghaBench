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
typedef  scalar_t__ u32 ;
struct clk_hw {struct clk_init_data* init; } ;
struct clk_scu {struct clk_hw hw; int /*<<< orphan*/  clk_type; scalar_t__ rsrc_id; } ;
struct clk_init_data {char const* name; char const* const* parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_GET_RATE_NOCACHE ; 
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMX_SC_R_A35 ; 
 int clk_hw_register (int /*<<< orphan*/ *,struct clk_hw*) ; 
 int /*<<< orphan*/  clk_scu_cpu_ops ; 
 int /*<<< orphan*/  clk_scu_ops ; 
 int /*<<< orphan*/  kfree (struct clk_scu*) ; 
 struct clk_scu* kzalloc (int,int /*<<< orphan*/ ) ; 

struct clk_hw *__imx_clk_scu(const char *name, const char * const *parents,
			     int num_parents, u32 rsrc_id, u8 clk_type)
{
	struct clk_init_data init;
	struct clk_scu *clk;
	struct clk_hw *hw;
	int ret;

	clk = kzalloc(sizeof(*clk), GFP_KERNEL);
	if (!clk)
		return ERR_PTR(-ENOMEM);

	clk->rsrc_id = rsrc_id;
	clk->clk_type = clk_type;

	init.name = name;
	init.ops = &clk_scu_ops;
	if (rsrc_id == IMX_SC_R_A35)
		init.ops = &clk_scu_cpu_ops;
	else
		init.ops = &clk_scu_ops;
	init.parent_names = parents;
	init.num_parents = num_parents;

	/*
	 * Note on MX8, the clocks are tightly coupled with power domain
	 * that once the power domain is off, the clock status may be
	 * lost. So we make it NOCACHE to let user to retrieve the real
	 * clock status from HW instead of using the possible invalid
	 * cached rate.
	 */
	init.flags = CLK_GET_RATE_NOCACHE;
	clk->hw.init = &init;

	hw = &clk->hw;
	ret = clk_hw_register(NULL, hw);
	if (ret) {
		kfree(clk);
		hw = ERR_PTR(ret);
	}

	return hw;
}