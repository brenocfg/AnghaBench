#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct acpi_cpu_softc {int /*<<< orphan*/  cpu_handle; scalar_t__ cpu_non_c3; int /*<<< orphan*/  cpu_cx_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  AcpiInstallNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_cpu_softc*) ; 
 int CPU_QUIRK_NO_C3 ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_cpu_devclass ; 
 int /*<<< orphan*/  acpi_cpu_generic_cx_probe (struct acpi_cpu_softc*) ; 
 int /*<<< orphan*/  acpi_cpu_global_cx_lowest_sysctl ; 
 int /*<<< orphan*/  acpi_cpu_idle ; 
 int /*<<< orphan*/  acpi_cpu_notify ; 
 int /*<<< orphan*/  acpi_cpu_quirks () ; 
 int /*<<< orphan*/  acpi_cpu_startup_cx (struct acpi_cpu_softc*) ; 
 scalar_t__ cpu_cx_generic ; 
 scalar_t__ cpu_cx_lowest_lim ; 
 int /*<<< orphan*/ * cpu_devices ; 
 int /*<<< orphan*/  cpu_idle_hook ; 
 int cpu_ndevices ; 
 int cpu_quirks ; 
 int /*<<< orphan*/  cpu_sysctl_ctx ; 
 int /*<<< orphan*/  cpu_sysctl_tree ; 
 int /*<<< orphan*/  devclass_get_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct acpi_cpu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_idle (struct acpi_cpu_softc*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
acpi_cpu_startup(void *arg)
{
    struct acpi_cpu_softc *sc;
    int i;

    /* Get set of CPU devices */
    devclass_get_devices(acpi_cpu_devclass, &cpu_devices, &cpu_ndevices);

    /*
     * Setup any quirks that might necessary now that we have probed
     * all the CPUs
     */
    acpi_cpu_quirks();

    if (cpu_cx_generic) {
	/*
	 * We are using generic Cx mode, probe for available Cx states
	 * for all processors.
	 */
	for (i = 0; i < cpu_ndevices; i++) {
	    sc = device_get_softc(cpu_devices[i]);
	    acpi_cpu_generic_cx_probe(sc);
	}
    } else {
	/*
	 * We are using _CST mode, remove C3 state if necessary.
	 * As we now know for sure that we will be using _CST mode
	 * install our notify handler.
	 */
	for (i = 0; i < cpu_ndevices; i++) {
	    sc = device_get_softc(cpu_devices[i]);
	    if (cpu_quirks & CPU_QUIRK_NO_C3) {
		sc->cpu_cx_count = min(sc->cpu_cx_count, sc->cpu_non_c3 + 1);
	    }
	    AcpiInstallNotifyHandler(sc->cpu_handle, ACPI_DEVICE_NOTIFY,
		acpi_cpu_notify, sc);
	}
    }

    /* Perform Cx final initialization. */
    for (i = 0; i < cpu_ndevices; i++) {
	sc = device_get_softc(cpu_devices[i]);
	acpi_cpu_startup_cx(sc);
    }

    /* Add a sysctl handler to handle global Cx lowest setting */
    SYSCTL_ADD_PROC(&cpu_sysctl_ctx, SYSCTL_CHILDREN(cpu_sysctl_tree),
	OID_AUTO, "cx_lowest", CTLTYPE_STRING | CTLFLAG_RW,
	NULL, 0, acpi_cpu_global_cx_lowest_sysctl, "A",
	"Global lowest Cx sleep state to use");

    /* Take over idling from cpu_idle_default(). */
    cpu_cx_lowest_lim = 0;
    for (i = 0; i < cpu_ndevices; i++) {
	sc = device_get_softc(cpu_devices[i]);
	enable_idle(sc);
    }
#if defined(__i386__) || defined(__amd64__)
    cpu_idle_hook = acpi_cpu_idle;
#endif
}