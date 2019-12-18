#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r9a06g032_priv {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sel; } ;
struct r9a06g032_clkdesc {TYPE_1__ dual; int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct clk_init_data* init; } ;
struct r9a06g032_clk_bitsel {TYPE_2__ hw; int /*<<< orphan*/  selector; int /*<<< orphan*/  index; struct r9a06g032_priv* clocks; } ;
struct clk_init_data {char const** parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_bitselect_ops ; 
 struct clk* clk_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct r9a06g032_clk_bitsel*) ; 
 struct r9a06g032_clk_bitsel* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *
r9a06g032_register_bitsel(struct r9a06g032_priv *clocks,
			  const char *parent_name,
			  const struct r9a06g032_clkdesc *desc)
{
	struct clk *clk;
	struct r9a06g032_clk_bitsel *g;
	struct clk_init_data init;
	const char *names[2];

	/* allocate the gate */
	g = kzalloc(sizeof(*g), GFP_KERNEL);
	if (!g)
		return NULL;

	names[0] = parent_name;
	names[1] = "clk_pll_usb";

	init.name = desc->name;
	init.ops = &clk_bitselect_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = names;
	init.num_parents = 2;

	g->clocks = clocks;
	g->index = desc->index;
	g->selector = desc->dual.sel;
	g->hw.init = &init;

	clk = clk_register(NULL, &g->hw);
	if (IS_ERR(clk)) {
		kfree(g);
		return NULL;
	}
	return clk;
}