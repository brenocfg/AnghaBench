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
struct tegra_dfll {TYPE_1__* dev; int /*<<< orphan*/  output_clock_name; int /*<<< orphan*/  cg_scale; int /*<<< orphan*/  cg; int /*<<< orphan*/  ci; int /*<<< orphan*/  cf; int /*<<< orphan*/  force_mode; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  droop_ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_property_read_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int read_dt_param (struct tegra_dfll*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dfll_fetch_common_params(struct tegra_dfll *td)
{
	bool ok = true;

	ok &= read_dt_param(td, "nvidia,droop-ctrl", &td->droop_ctrl);
	ok &= read_dt_param(td, "nvidia,sample-rate", &td->sample_rate);
	ok &= read_dt_param(td, "nvidia,force-mode", &td->force_mode);
	ok &= read_dt_param(td, "nvidia,cf", &td->cf);
	ok &= read_dt_param(td, "nvidia,ci", &td->ci);
	ok &= read_dt_param(td, "nvidia,cg", &td->cg);
	td->cg_scale = of_property_read_bool(td->dev->of_node,
					     "nvidia,cg-scale");

	if (of_property_read_string(td->dev->of_node, "clock-output-names",
				    &td->output_clock_name)) {
		dev_err(td->dev, "missing clock-output-names property\n");
		ok = false;
	}

	return ok ? 0 : -EINVAL;
}