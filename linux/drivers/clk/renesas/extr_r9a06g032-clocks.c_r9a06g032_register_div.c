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
struct r9a06g032_priv {int dummy; } ;
struct r9a06g032_clkdesc {scalar_t__* div_table; int /*<<< orphan*/  div_max; int /*<<< orphan*/  div_min; int /*<<< orphan*/  reg; int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct r9a06g032_clk_div {TYPE_1__ hw; int /*<<< orphan*/  table_size; scalar_t__* table; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  reg; int /*<<< orphan*/  index; struct r9a06g032_priv* clocks; } ;
struct clk_init_data {char const** parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 struct clk* clk_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct r9a06g032_clk_div*) ; 
 struct r9a06g032_clk_div* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r9a06g032_clk_div_ops ; 

__attribute__((used)) static struct clk *
r9a06g032_register_div(struct r9a06g032_priv *clocks,
		       const char *parent_name,
		       const struct r9a06g032_clkdesc *desc)
{
	struct r9a06g032_clk_div *div;
	struct clk *clk;
	struct clk_init_data init;
	unsigned int i;

	div = kzalloc(sizeof(*div), GFP_KERNEL);
	if (!div)
		return NULL;

	init.name = desc->name;
	init.ops = &r9a06g032_clk_div_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_name ? &parent_name : NULL;
	init.num_parents = parent_name ? 1 : 0;

	div->clocks = clocks;
	div->index = desc->index;
	div->reg = desc->reg;
	div->hw.init = &init;
	div->min = desc->div_min;
	div->max = desc->div_max;
	/* populate (optional) divider table fixed values */
	for (i = 0; i < ARRAY_SIZE(div->table) &&
	     i < ARRAY_SIZE(desc->div_table) && desc->div_table[i]; i++) {
		div->table[div->table_size++] = desc->div_table[i];
	}

	clk = clk_register(NULL, &div->hw);
	if (IS_ERR(clk)) {
		kfree(div);
		return NULL;
	}
	return clk;
}