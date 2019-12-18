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
struct acpi_toshiba_softc {int /*<<< orphan*/  handle; int /*<<< orphan*/  sysctl_ctx; int /*<<< orphan*/  sysctl_tree; int /*<<< orphan*/  dev; } ;
struct acpi_softc {int /*<<< orphan*/  acpi_sysctl_tree; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiInstallNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_toshiba_softc*) ; 
 int CTLFLAG_ANYBODY ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  METHOD_HCI_ENABLE ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct acpi_toshiba_softc*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct acpi_softc* acpi_device_get_parent_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_toshiba_notify ; 
 int /*<<< orphan*/  acpi_toshiba_sysctl ; 
 struct acpi_toshiba_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ enable_fn_keys ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* sysctl_table ; 

__attribute__((used)) static int
acpi_toshiba_attach(device_t dev)
{
	struct		acpi_toshiba_softc *sc;
	struct		acpi_softc *acpi_sc;
	ACPI_STATUS	status;
	int		i;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->handle = acpi_get_handle(dev);

	acpi_sc = acpi_device_get_parent_softc(dev);
	sysctl_ctx_init(&sc->sysctl_ctx);
	sc->sysctl_tree = SYSCTL_ADD_NODE(&sc->sysctl_ctx,
	    SYSCTL_CHILDREN(acpi_sc->acpi_sysctl_tree), OID_AUTO,
	    "toshiba", CTLFLAG_RD, 0, "");

	for (i = 0; sysctl_table[i].name != NULL; i++) {
		SYSCTL_ADD_PROC(&sc->sysctl_ctx,
		    SYSCTL_CHILDREN(sc->sysctl_tree), OID_AUTO,
		    sysctl_table[i].name,
		    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_ANYBODY,
		    sc, i, acpi_toshiba_sysctl, "I", "");
	}

	if (enable_fn_keys != 0) {
		status = AcpiEvaluateObject(sc->handle, METHOD_HCI_ENABLE,
					    NULL, NULL);
		if (ACPI_FAILURE(status)) {
			device_printf(dev, "enable FN keys failed\n");
			sysctl_ctx_free(&sc->sysctl_ctx);
			return (ENXIO);
		}
		AcpiInstallNotifyHandler(sc->handle, ACPI_DEVICE_NOTIFY,
					 acpi_toshiba_notify, sc);
	}

	return (0);
}