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
struct acpi_battinfo {int min; int /*<<< orphan*/  cap; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  TYPE_1__* apm_pwstatus_t ;
struct TYPE_3__ {scalar_t__ ap_device; int ap_batt_time; int ap_acline; int /*<<< orphan*/  ap_batt_life; int /*<<< orphan*/  ap_batt_flag; int /*<<< orphan*/  ap_batt_stat; } ;

/* Variables and functions */
 int APM_UNKNOWN ; 
 int ENXIO ; 
 scalar_t__ PMDV_ALLDEV ; 
 scalar_t__ PMDV_BATT0 ; 
 scalar_t__ PMDV_BATT_ALL ; 
 scalar_t__ acpi_acad_get_acline (int*) ; 
 int acpi_battery_get_battinfo (int /*<<< orphan*/ *,struct acpi_battinfo*) ; 
 int /*<<< orphan*/  acpi_capm_convert_battflags (struct acpi_battinfo*) ; 
 int /*<<< orphan*/  acpi_capm_convert_battstate (struct acpi_battinfo*) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_capm_get_pwstatus(apm_pwstatus_t app)
{
	device_t dev;
	int	acline, unit, error;
	struct	acpi_battinfo batt;

	if (app->ap_device != PMDV_ALLDEV &&
	    (app->ap_device < PMDV_BATT0 || app->ap_device > PMDV_BATT_ALL))
		return (1);

	if (app->ap_device == PMDV_ALLDEV)
		error = acpi_battery_get_battinfo(NULL, &batt);
	else {
		unit = app->ap_device - PMDV_BATT0;
		dev = devclass_get_device(devclass_find("battery"), unit);
		if (dev != NULL)
			error = acpi_battery_get_battinfo(dev, &batt);
		else
			error = ENXIO;
	}
	if (error)
		return (1);

	app->ap_batt_stat = acpi_capm_convert_battstate(&batt);
	app->ap_batt_flag = acpi_capm_convert_battflags(&batt);
	app->ap_batt_life = batt.cap;
	app->ap_batt_time = (batt.min == -1) ? -1 : batt.min * 60;

	if (acpi_acad_get_acline(&acline))
		app->ap_acline = APM_UNKNOWN;
	else
		app->ap_acline = acline;	/* on/off */

	return (0);
}