#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ti_sysc_platform_data {int /*<<< orphan*/ * auxdata; } ;
struct TYPE_11__ {int quirks; } ;
struct sysc {int /*<<< orphan*/  idle_work; TYPE_1__ cfg; TYPE_2__* dev; scalar_t__ rsts; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * type; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SYSC_QUIRK_NO_IDLE ; 
 int SYSC_QUIRK_NO_IDLE_ON_INIT ; 
 int SYSC_QUIRK_NO_RESET_ON_INIT ; 
 struct ti_sysc_platform_data* dev_get_platdata (TYPE_2__*) ; 
 struct sysc* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sysc*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  reset_control_assert (scalar_t__) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sysc_device_type ; 
 int sysc_get_clocks (struct sysc*) ; 
 int sysc_init_dts_quirks (struct sysc*) ; 
 int /*<<< orphan*/  sysc_init_early_quirks (struct sysc*) ; 
 int sysc_init_idlemodes (struct sysc*) ; 
 int sysc_init_match (struct sysc*) ; 
 int sysc_init_module (struct sysc*) ; 
 int sysc_init_pdata (struct sysc*) ; 
 int sysc_init_resets (struct sysc*) ; 
 int sysc_init_sysc_mask (struct sysc*) ; 
 int sysc_init_syss_mask (struct sysc*) ; 
 int sysc_map_and_check_registers (struct sysc*) ; 
 int /*<<< orphan*/  sysc_match_table ; 
 int /*<<< orphan*/  sysc_show_registers (struct sysc*) ; 
 int /*<<< orphan*/  sysc_unprepare (struct sysc*) ; 
 int /*<<< orphan*/  ti_sysc_idle ; 

__attribute__((used)) static int sysc_probe(struct platform_device *pdev)
{
	struct ti_sysc_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct sysc *ddata;
	int error;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	ddata->dev = &pdev->dev;
	platform_set_drvdata(pdev, ddata);

	error = sysc_init_match(ddata);
	if (error)
		return error;

	error = sysc_init_dts_quirks(ddata);
	if (error)
		return error;

	error = sysc_map_and_check_registers(ddata);
	if (error)
		return error;

	error = sysc_init_sysc_mask(ddata);
	if (error)
		return error;

	error = sysc_init_idlemodes(ddata);
	if (error)
		return error;

	error = sysc_init_syss_mask(ddata);
	if (error)
		return error;

	error = sysc_init_pdata(ddata);
	if (error)
		return error;

	sysc_init_early_quirks(ddata);

	error = sysc_get_clocks(ddata);
	if (error)
		return error;

	error = sysc_init_resets(ddata);
	if (error)
		goto unprepare;

	error = sysc_init_module(ddata);
	if (error)
		goto unprepare;

	pm_runtime_enable(ddata->dev);
	error = pm_runtime_get_sync(ddata->dev);
	if (error < 0) {
		pm_runtime_put_noidle(ddata->dev);
		pm_runtime_disable(ddata->dev);
		goto unprepare;
	}

	/* Balance reset counts */
	if (ddata->rsts)
		reset_control_assert(ddata->rsts);

	sysc_show_registers(ddata);

	ddata->dev->type = &sysc_device_type;
	error = of_platform_populate(ddata->dev->of_node, sysc_match_table,
				     pdata ? pdata->auxdata : NULL,
				     ddata->dev);
	if (error)
		goto err;

	INIT_DELAYED_WORK(&ddata->idle_work, ti_sysc_idle);

	/* At least earlycon won't survive without deferred idle */
	if (ddata->cfg.quirks & (SYSC_QUIRK_NO_IDLE |
				 SYSC_QUIRK_NO_IDLE_ON_INIT |
				 SYSC_QUIRK_NO_RESET_ON_INIT)) {
		schedule_delayed_work(&ddata->idle_work, 3000);
	} else {
		pm_runtime_put(&pdev->dev);
	}

	return 0;

err:
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
unprepare:
	sysc_unprepare(ddata);

	return error;
}