#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct clk_init_data* init; } ;
struct TYPE_6__ {TYPE_4__ hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  clks; } ;
struct ti_adpll_data {TYPE_3__* c; TYPE_2__ dco; int /*<<< orphan*/  dev; scalar_t__ regs; int /*<<< orphan*/ * parent_clocks; int /*<<< orphan*/  parent_names; TYPE_1__ outputs; } ;
struct clk_init_data {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; } ;
struct clk {int dummy; } ;
struct TYPE_7__ {scalar_t__ output_index; scalar_t__ is_type_s; int /*<<< orphan*/  nr_max_inputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADPLL_MN2DIV_N2 ; 
 scalar_t__ ADPLL_MN2DIV_OFFSET ; 
 int /*<<< orphan*/  CLK_GET_RATE_NOCACHE ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  MAX_ADPLL_OUTPUTS ; 
 int PTR_ERR (struct clk*) ; 
 size_t TI_ADPLL_CLKINP ; 
 int /*<<< orphan*/  TI_ADPLL_DCO ; 
 int /*<<< orphan*/  TI_ADPLL_N2 ; 
 struct clk* devm_clk_register (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_adpll_clk_get_name (struct ti_adpll_data*,scalar_t__,char const*) ; 
 int ti_adpll_init_divider (struct ti_adpll_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_adpll_ops ; 
 int ti_adpll_setup_clock (struct ti_adpll_data*,struct clk*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ti_adpll_init_dco(struct ti_adpll_data *d)
{
	struct clk_init_data init;
	struct clk *clock;
	const char *postfix;
	int width, err;

	d->outputs.clks = devm_kcalloc(d->dev,
				       MAX_ADPLL_OUTPUTS,
				       sizeof(struct clk *),
				       GFP_KERNEL);
	if (!d->outputs.clks)
		return -ENOMEM;

	if (d->c->output_index < 0)
		postfix = "dco";
	else
		postfix = NULL;

	init.name = ti_adpll_clk_get_name(d, d->c->output_index, postfix);
	if (!init.name)
		return -EINVAL;

	init.parent_names = d->parent_names;
	init.num_parents = d->c->nr_max_inputs;
	init.ops = &ti_adpll_ops;
	init.flags = CLK_GET_RATE_NOCACHE;
	d->dco.hw.init = &init;

	if (d->c->is_type_s)
		width = 5;
	else
		width = 4;

	/* Internal input clock divider N2 */
	err = ti_adpll_init_divider(d, TI_ADPLL_N2, -ENODEV, "n2",
				    d->parent_clocks[TI_ADPLL_CLKINP],
				    d->regs + ADPLL_MN2DIV_OFFSET,
				    ADPLL_MN2DIV_N2, width, 0);
	if (err)
		return err;

	clock = devm_clk_register(d->dev, &d->dco.hw);
	if (IS_ERR(clock))
		return PTR_ERR(clock);

	return ti_adpll_setup_clock(d, clock, TI_ADPLL_DCO, d->c->output_index,
				    init.name, NULL);
}