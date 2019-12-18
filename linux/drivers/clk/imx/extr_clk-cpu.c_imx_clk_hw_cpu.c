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
struct clk_init_data {char const* name; char const** parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct clk_hw {struct clk_init_data* init; } ;
struct clk_cpu {struct clk_hw hw; struct clk* step; struct clk* pll; struct clk* mux; struct clk* div; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_IS_CRITICAL ; 
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clk_cpu_ops ; 
 int clk_hw_register (int /*<<< orphan*/ *,struct clk_hw*) ; 
 int /*<<< orphan*/  kfree (struct clk_cpu*) ; 
 struct clk_cpu* kzalloc (int,int /*<<< orphan*/ ) ; 

struct clk_hw *imx_clk_hw_cpu(const char *name, const char *parent_name,
		struct clk *div, struct clk *mux, struct clk *pll,
		struct clk *step)
{
	struct clk_cpu *cpu;
	struct clk_hw *hw;
	struct clk_init_data init;
	int ret;

	cpu = kzalloc(sizeof(*cpu), GFP_KERNEL);
	if (!cpu)
		return ERR_PTR(-ENOMEM);

	cpu->div = div;
	cpu->mux = mux;
	cpu->pll = pll;
	cpu->step = step;

	init.name = name;
	init.ops = &clk_cpu_ops;
	init.flags = CLK_IS_CRITICAL;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	cpu->hw.init = &init;
	hw = &cpu->hw;

	ret = clk_hw_register(NULL, hw);
	if (ret) {
		kfree(cpu);
		return ERR_PTR(ret);
	}

	return hw;
}