#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  oeminfo; int /*<<< orphan*/  type; int /*<<< orphan*/  serial; int /*<<< orphan*/  model; } ;
union acpi_battery_ioctl_arg {int unit; TYPE_1__ bst; TYPE_1__ bif; TYPE_1__ battinfo; } ;
typedef  int u_long ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  ACPIIO_BATT_GET_BATTINFO 131 
#define  ACPIIO_BATT_GET_BIF 130 
#define  ACPIIO_BATT_GET_BST 129 
#define  ACPIIO_BATT_GET_UNITS 128 
 int ACPI_BATTERY_ALL_UNITS ; 
 int ACPI_BATT_GET_INFO (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int ACPI_BATT_GET_STATUS (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int EINVAL ; 
 int ENXIO ; 
 int IOCPARM_LEN (int) ; 
 int /*<<< orphan*/  acpi_battery_clean_str (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * acpi_battery_find_dev (int) ; 
 int acpi_battery_get_battinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int acpi_battery_get_units () ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 

__attribute__((used)) static int
acpi_battery_ioctl(u_long cmd, caddr_t addr, void *arg)
{
    union acpi_battery_ioctl_arg *ioctl_arg;
    int error, unit;
    device_t dev;

    /* For commands that use the ioctl_arg struct, validate it first. */
    error = ENXIO;
    unit = 0;
    dev = NULL;
    ioctl_arg = NULL;
    if (IOCPARM_LEN(cmd) == sizeof(*ioctl_arg)) {
	ioctl_arg = (union acpi_battery_ioctl_arg *)addr;
	unit = ioctl_arg->unit;
	if (unit != ACPI_BATTERY_ALL_UNITS)
	    dev = acpi_battery_find_dev(unit);
    }

    /*
     * No security check required: information retrieval only.  If
     * new functions are added here, a check might be required.
     */
    switch (cmd) {
    case ACPIIO_BATT_GET_UNITS:
	*(int *)addr = acpi_battery_get_units();
	error = 0;
	break;
    case ACPIIO_BATT_GET_BATTINFO:
	if (dev != NULL || unit == ACPI_BATTERY_ALL_UNITS) {
	    bzero(&ioctl_arg->battinfo, sizeof(ioctl_arg->battinfo));
	    error = acpi_battery_get_battinfo(dev, &ioctl_arg->battinfo);
	}
	break;
    case ACPIIO_BATT_GET_BIF:
	if (dev != NULL) {
	    bzero(&ioctl_arg->bif, sizeof(ioctl_arg->bif));
	    error = ACPI_BATT_GET_INFO(dev, &ioctl_arg->bif);

	    /*
	     * Remove invalid characters.  Perhaps this should be done
	     * within a convenience function so all callers get the
	     * benefit.
	     */
	    acpi_battery_clean_str(ioctl_arg->bif.model,
		sizeof(ioctl_arg->bif.model));
	    acpi_battery_clean_str(ioctl_arg->bif.serial,
		sizeof(ioctl_arg->bif.serial));
	    acpi_battery_clean_str(ioctl_arg->bif.type,
		sizeof(ioctl_arg->bif.type));
	    acpi_battery_clean_str(ioctl_arg->bif.oeminfo,
		sizeof(ioctl_arg->bif.oeminfo));
	}
	break;
    case ACPIIO_BATT_GET_BST:
	if (dev != NULL) {
	    bzero(&ioctl_arg->bst, sizeof(ioctl_arg->bst));
	    error = ACPI_BATT_GET_STATUS(dev, &ioctl_arg->bst);
	}
	break;
    default:
	error = EINVAL;
    }

    return (error);
}