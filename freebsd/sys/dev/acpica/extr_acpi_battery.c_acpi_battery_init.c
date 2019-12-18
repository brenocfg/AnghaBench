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
struct acpi_softc {int /*<<< orphan*/  acpi_sysctl_tree; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  rate; int /*<<< orphan*/  min; int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPIIO_BATT_GET_BATTINFO ; 
 int /*<<< orphan*/  ACPIIO_BATT_GET_BIF ; 
 int /*<<< orphan*/  ACPIIO_BATT_GET_BST ; 
 int /*<<< orphan*/  ACPIIO_BATT_GET_UNITS ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_batteries_initted ; 
 TYPE_1__ acpi_battery_battinfo ; 
 int /*<<< orphan*/  acpi_battery_info_expire ; 
 int /*<<< orphan*/  acpi_battery_ioctl ; 
 int /*<<< orphan*/  acpi_battery_sysctl ; 
 int /*<<< orphan*/  acpi_battery_sysctl_ctx ; 
 int /*<<< orphan*/  acpi_battery_sysctl_tree ; 
 int /*<<< orphan*/  acpi_battery_units_sysctl ; 
 int /*<<< orphan*/  acpi_deregister_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acpi_register_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  battery ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_battery_init(void)
{
    struct acpi_softc	*sc;
    device_t		 dev;
    int	 		 error;

    ACPI_SERIAL_ASSERT(battery);

    error = ENXIO;
    dev = devclass_get_device(devclass_find("acpi"), 0);
    if (dev == NULL)
	goto out;
    sc = device_get_softc(dev);

    error = acpi_register_ioctl(ACPIIO_BATT_GET_UNITS, acpi_battery_ioctl,
	NULL);
    if (error != 0)
	goto out;
    error = acpi_register_ioctl(ACPIIO_BATT_GET_BATTINFO, acpi_battery_ioctl,
	NULL);
    if (error != 0)
	goto out;
    error = acpi_register_ioctl(ACPIIO_BATT_GET_BIF, acpi_battery_ioctl, NULL);
    if (error != 0)
	goto out;
    error = acpi_register_ioctl(ACPIIO_BATT_GET_BST, acpi_battery_ioctl, NULL);
    if (error != 0)
	goto out;

    sysctl_ctx_init(&acpi_battery_sysctl_ctx);
    acpi_battery_sysctl_tree = SYSCTL_ADD_NODE(&acpi_battery_sysctl_ctx,
	SYSCTL_CHILDREN(sc->acpi_sysctl_tree), OID_AUTO, "battery", CTLFLAG_RD,
	0, "battery status and info");
    SYSCTL_ADD_PROC(&acpi_battery_sysctl_ctx,
	SYSCTL_CHILDREN(acpi_battery_sysctl_tree),
	OID_AUTO, "life", CTLTYPE_INT | CTLFLAG_RD,
	&acpi_battery_battinfo.cap, 0, acpi_battery_sysctl, "I",
	"percent capacity remaining");
    SYSCTL_ADD_PROC(&acpi_battery_sysctl_ctx,
	SYSCTL_CHILDREN(acpi_battery_sysctl_tree),
	OID_AUTO, "time", CTLTYPE_INT | CTLFLAG_RD,
	&acpi_battery_battinfo.min, 0, acpi_battery_sysctl, "I",
	"remaining time in minutes");
    SYSCTL_ADD_PROC(&acpi_battery_sysctl_ctx,
	SYSCTL_CHILDREN(acpi_battery_sysctl_tree),
	OID_AUTO, "rate", CTLTYPE_INT | CTLFLAG_RD,
	&acpi_battery_battinfo.rate, 0, acpi_battery_sysctl, "I",
	"present rate in mW");
    SYSCTL_ADD_PROC(&acpi_battery_sysctl_ctx,
	SYSCTL_CHILDREN(acpi_battery_sysctl_tree),
	OID_AUTO, "state", CTLTYPE_INT | CTLFLAG_RD,
	&acpi_battery_battinfo.state, 0, acpi_battery_sysctl, "I",
	"current status flags");
    SYSCTL_ADD_PROC(&acpi_battery_sysctl_ctx,
	SYSCTL_CHILDREN(acpi_battery_sysctl_tree),
	OID_AUTO, "units", CTLTYPE_INT | CTLFLAG_RD,
	NULL, 0, acpi_battery_units_sysctl, "I", "number of batteries");
    SYSCTL_ADD_INT(&acpi_battery_sysctl_ctx,
	SYSCTL_CHILDREN(acpi_battery_sysctl_tree),
	OID_AUTO, "info_expire", CTLFLAG_RW,
	&acpi_battery_info_expire, 0,
	"time in seconds until info is refreshed");

    acpi_batteries_initted = TRUE;

out:
    if (error != 0) {
	acpi_deregister_ioctl(ACPIIO_BATT_GET_UNITS, acpi_battery_ioctl);
	acpi_deregister_ioctl(ACPIIO_BATT_GET_BATTINFO, acpi_battery_ioctl);
	acpi_deregister_ioctl(ACPIIO_BATT_GET_BIF, acpi_battery_ioctl);
	acpi_deregister_ioctl(ACPIIO_BATT_GET_BST, acpi_battery_ioctl);
    }
    return (error);
}