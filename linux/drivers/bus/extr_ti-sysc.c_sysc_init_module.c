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
struct TYPE_2__ {int quirks; } ;
struct sysc {int /*<<< orphan*/  dev; scalar_t__ legacy_mode; int /*<<< orphan*/  revision; TYPE_1__ cfg; } ;

/* Variables and functions */
 int SYSC_QUIRK_NO_IDLE ; 
 int SYSC_QUIRK_NO_IDLE_ON_INIT ; 
 int SYSC_QUIRK_NO_RESET_ON_INIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sysc_clkdm_allow_idle (struct sysc*) ; 
 int /*<<< orphan*/  sysc_clkdm_deny_idle (struct sysc*) ; 
 int sysc_clockdomain_init (struct sysc*) ; 
 int /*<<< orphan*/  sysc_disable_main_clocks (struct sysc*) ; 
 int /*<<< orphan*/  sysc_disable_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysc_disable_opt_clocks (struct sysc*) ; 
 int sysc_enable_main_clocks (struct sysc*) ; 
 int sysc_enable_module (int /*<<< orphan*/ ) ; 
 int sysc_enable_opt_clocks (struct sysc*) ; 
 int /*<<< orphan*/  sysc_init_module_quirks (struct sysc*) ; 
 int /*<<< orphan*/  sysc_init_revision_quirks (struct sysc*) ; 
 int sysc_legacy_init (struct sysc*) ; 
 int /*<<< orphan*/  sysc_read_revision (struct sysc*) ; 
 int sysc_reset (struct sysc*) ; 
 int sysc_rstctrl_reset_deassert (struct sysc*,int) ; 

__attribute__((used)) static int sysc_init_module(struct sysc *ddata)
{
	int error = 0;
	bool manage_clocks = true;

	error = sysc_rstctrl_reset_deassert(ddata, false);
	if (error)
		return error;

	if (ddata->cfg.quirks &
	    (SYSC_QUIRK_NO_IDLE | SYSC_QUIRK_NO_IDLE_ON_INIT))
		manage_clocks = false;

	error = sysc_clockdomain_init(ddata);
	if (error)
		return error;

	sysc_clkdm_deny_idle(ddata);

	/*
	 * Always enable clocks. The bootloader may or may not have enabled
	 * the related clocks.
	 */
	error = sysc_enable_opt_clocks(ddata);
	if (error)
		return error;

	error = sysc_enable_main_clocks(ddata);
	if (error)
		goto err_opt_clocks;

	if (!(ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT)) {
		error = sysc_rstctrl_reset_deassert(ddata, true);
		if (error)
			goto err_main_clocks;
	}

	ddata->revision = sysc_read_revision(ddata);
	sysc_init_revision_quirks(ddata);
	sysc_init_module_quirks(ddata);

	if (ddata->legacy_mode) {
		error = sysc_legacy_init(ddata);
		if (error)
			goto err_main_clocks;
	}

	if (!ddata->legacy_mode) {
		error = sysc_enable_module(ddata->dev);
		if (error)
			goto err_main_clocks;
	}

	error = sysc_reset(ddata);
	if (error)
		dev_err(ddata->dev, "Reset failed with %d\n", error);

	if (!ddata->legacy_mode && manage_clocks)
		sysc_disable_module(ddata->dev);

err_main_clocks:
	if (manage_clocks)
		sysc_disable_main_clocks(ddata);
err_opt_clocks:
	/* No re-enable of clockdomain autoidle to prevent module autoidle */
	if (manage_clocks) {
		sysc_disable_opt_clocks(ddata);
		sysc_clkdm_allow_idle(ddata);
	}

	return error;
}