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
struct acpi_sony_softc {int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  comment; int /*<<< orphan*/ * nodename; int /*<<< orphan*/ * setmethod; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SONY_GET_PID ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 TYPE_1__* acpi_sony_oids ; 
 struct acpi_sony_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_acpi_sony_gen_handler ; 

__attribute__((used)) static int
acpi_sony_attach(device_t dev)
{
	struct acpi_sony_softc *sc;
	int i;

	sc = device_get_softc(dev);
	acpi_GetInteger(acpi_get_handle(dev), ACPI_SONY_GET_PID, &sc->pid);
	device_printf(dev, "PID %x\n", sc->pid);
	for (i = 0 ; acpi_sony_oids[i].nodename != NULL; i++) {
		if (acpi_sony_oids[i].setmethod != NULL) {
			SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
			    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
			    i, acpi_sony_oids[i].nodename ,
			    CTLTYPE_INT | CTLFLAG_RW,
			    dev, i, sysctl_acpi_sony_gen_handler, "I",
			    acpi_sony_oids[i].comment);
		} else {
			SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
			    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
			    i, acpi_sony_oids[i].nodename ,
			    CTLTYPE_INT | CTLFLAG_RD,
			    dev, i, sysctl_acpi_sony_gen_handler, "I",
			    acpi_sony_oids[i].comment);
		}
	}
	return (0);
}