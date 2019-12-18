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
struct tegra_dfll {scalar_t__ ref_rate; int /*<<< orphan*/  dvco_rst; int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  soc_clk; int /*<<< orphan*/  dev; TYPE_1__* soc; scalar_t__ last_unrounded_rate; int /*<<< orphan*/  i2c_clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_clock_trimmers ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_DISABLED ; 
 int EINVAL ; 
 scalar_t__ REF_CLOCK_RATE ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dfll_init_out_if (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_set_default_params (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_set_mode (struct tegra_dfll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfll_set_open_loop_config (struct tegra_dfll*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int dfll_init(struct tegra_dfll *td)
{
	int ret;

	td->ref_rate = clk_get_rate(td->ref_clk);
	if (td->ref_rate != REF_CLOCK_RATE) {
		dev_err(td->dev, "unexpected ref clk rate %lu, expecting %lu",
			td->ref_rate, REF_CLOCK_RATE);
		return -EINVAL;
	}

	reset_control_deassert(td->dvco_rst);

	ret = clk_prepare(td->ref_clk);
	if (ret) {
		dev_err(td->dev, "failed to prepare ref_clk\n");
		return ret;
	}

	ret = clk_prepare(td->soc_clk);
	if (ret) {
		dev_err(td->dev, "failed to prepare soc_clk\n");
		goto di_err1;
	}

	ret = clk_prepare(td->i2c_clk);
	if (ret) {
		dev_err(td->dev, "failed to prepare i2c_clk\n");
		goto di_err2;
	}

	td->last_unrounded_rate = 0;

	pm_runtime_enable(td->dev);
	pm_runtime_get_sync(td->dev);

	dfll_set_mode(td, DFLL_DISABLED);
	dfll_set_default_params(td);

	if (td->soc->init_clock_trimmers)
		td->soc->init_clock_trimmers();

	dfll_set_open_loop_config(td);

	dfll_init_out_if(td);

	pm_runtime_put_sync(td->dev);

	return 0;

di_err2:
	clk_unprepare(td->soc_clk);
di_err1:
	clk_unprepare(td->ref_clk);

	reset_control_assert(td->dvco_rst);

	return ret;
}