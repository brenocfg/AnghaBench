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
struct ti_adpll_data {struct clk** parent_clocks; int /*<<< orphan*/  dev; int /*<<< orphan*/ * parent_names; TYPE_1__* c; int /*<<< orphan*/  np; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int nr_max_inputs; scalar_t__ is_type_s; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 size_t TI_ADPLL_CLKINP ; 
 size_t TI_ADPLL_CLKINPHIF ; 
 size_t TI_ADPLL_CLKINPULOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char const*,...) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_clk_get_parent_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_parent_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ti_adpll_init_inputs(struct ti_adpll_data *d)
{
	const char *error = "need at least %i inputs";
	struct clk *clock;
	int nr_inputs;

	nr_inputs = of_clk_get_parent_count(d->np);
	if (nr_inputs < d->c->nr_max_inputs) {
		dev_err(d->dev, error, nr_inputs);
		return -EINVAL;
	}
	of_clk_parent_fill(d->np, d->parent_names, nr_inputs);

	clock = devm_clk_get(d->dev, d->parent_names[0]);
	if (IS_ERR(clock)) {
		dev_err(d->dev, "could not get clkinp\n");
		return PTR_ERR(clock);
	}
	d->parent_clocks[TI_ADPLL_CLKINP] = clock;

	clock = devm_clk_get(d->dev, d->parent_names[1]);
	if (IS_ERR(clock)) {
		dev_err(d->dev, "could not get clkinpulow clock\n");
		return PTR_ERR(clock);
	}
	d->parent_clocks[TI_ADPLL_CLKINPULOW] = clock;

	if (d->c->is_type_s) {
		clock =  devm_clk_get(d->dev, d->parent_names[2]);
		if (IS_ERR(clock)) {
			dev_err(d->dev, "could not get clkinphif clock\n");
			return PTR_ERR(clock);
		}
		d->parent_clocks[TI_ADPLL_CLKINPHIF] = clock;
	}

	return 0;
}