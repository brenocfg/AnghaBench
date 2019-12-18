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
struct sysc {void* module_disable_quirk; void* reset_done_quirk; TYPE_1__ cfg; int /*<<< orphan*/  module_enable_quirk; int /*<<< orphan*/  clk_disable_quirk; int /*<<< orphan*/  clk_enable_quirk; int /*<<< orphan*/  name; scalar_t__ legacy_mode; } ;

/* Variables and functions */
 int SYSC_MODULE_QUIRK_HDQ1W ; 
 int SYSC_MODULE_QUIRK_I2C ; 
 int SYSC_MODULE_QUIRK_SGX ; 
 int SYSC_MODULE_QUIRK_WDT ; 
 int /*<<< orphan*/  sysc_clk_disable_quirk_i2c ; 
 int /*<<< orphan*/  sysc_clk_enable_quirk_hdq1w ; 
 int /*<<< orphan*/  sysc_clk_enable_quirk_i2c ; 
 int /*<<< orphan*/  sysc_module_enable_quirk_sgx ; 
 void* sysc_reset_done_quirk_wdt ; 

__attribute__((used)) static void sysc_init_module_quirks(struct sysc *ddata)
{
	if (ddata->legacy_mode || !ddata->name)
		return;

	if (ddata->cfg.quirks & SYSC_MODULE_QUIRK_HDQ1W) {
		ddata->clk_enable_quirk = sysc_clk_enable_quirk_hdq1w;

		return;
	}

	if (ddata->cfg.quirks & SYSC_MODULE_QUIRK_I2C) {
		ddata->clk_enable_quirk = sysc_clk_enable_quirk_i2c;
		ddata->clk_disable_quirk = sysc_clk_disable_quirk_i2c;

		return;
	}

	if (ddata->cfg.quirks & SYSC_MODULE_QUIRK_SGX)
		ddata->module_enable_quirk = sysc_module_enable_quirk_sgx;

	if (ddata->cfg.quirks & SYSC_MODULE_QUIRK_WDT) {
		ddata->reset_done_quirk = sysc_reset_done_quirk_wdt;
		ddata->module_disable_quirk = sysc_reset_done_quirk_wdt;
	}
}