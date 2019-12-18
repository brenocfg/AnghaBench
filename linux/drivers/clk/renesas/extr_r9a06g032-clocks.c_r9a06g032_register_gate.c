#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r9a06g032_priv {int dummy; } ;
struct r9a06g032_clkdesc {int /*<<< orphan*/  name; int /*<<< orphan*/  gate; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {struct clk_init_data* init; } ;
struct r9a06g032_clk_gate {TYPE_1__ hw; int /*<<< orphan*/  gate; int /*<<< orphan*/  index; struct r9a06g032_priv* clocks; } ;
struct clk_init_data {char const** parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_IS_CRITICAL ; 
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 struct clk* clk_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct r9a06g032_clk_gate*) ; 
 struct r9a06g032_clk_gate* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ r9a06g032_clk_gate_is_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  r9a06g032_clk_gate_ops ; 

__attribute__((used)) static struct clk *
r9a06g032_register_gate(struct r9a06g032_priv *clocks,
			const char *parent_name,
			const struct r9a06g032_clkdesc *desc)
{
	struct clk *clk;
	struct r9a06g032_clk_gate *g;
	struct clk_init_data init;

	g = kzalloc(sizeof(*g), GFP_KERNEL);
	if (!g)
		return NULL;

	init.name = desc->name;
	init.ops = &r9a06g032_clk_gate_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_name ? &parent_name : NULL;
	init.num_parents = parent_name ? 1 : 0;

	g->clocks = clocks;
	g->index = desc->index;
	g->gate = desc->gate;
	g->hw.init = &init;

	/*
	 * important here, some clocks are already in use by the CM3, we
	 * have to assume they are not Linux's to play with and try to disable
	 * at the end of the boot!
	 */
	if (r9a06g032_clk_gate_is_enabled(&g->hw)) {
		init.flags |= CLK_IS_CRITICAL;
		pr_debug("%s was enabled, making read-only\n", desc->name);
	}

	clk = clk_register(NULL, &g->hw);
	if (IS_ERR(clk)) {
		kfree(g);
		return NULL;
	}
	return clk;
}