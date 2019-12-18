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
struct acpi_cpu_softc {int /*<<< orphan*/  cpu_dev; int /*<<< orphan*/  cpu_sysctl_ctx; int /*<<< orphan*/  cpu_cx_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsWritePort (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi ; 
 int /*<<< orphan*/  acpi_cpu_cx_list (struct acpi_cpu_softc*) ; 
 int /*<<< orphan*/  acpi_cpu_cx_lowest_sysctl ; 
 int /*<<< orphan*/  acpi_cpu_method_sysctl ; 
 int /*<<< orphan*/  acpi_cpu_usage_counters_sysctl ; 
 int /*<<< orphan*/  acpi_cpu_usage_sysctl ; 
 scalar_t__ cpu_cst_cnt ; 
 int /*<<< orphan*/  cpu_cx_generic ; 
 int /*<<< orphan*/  cpu_smi_cmd ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_cpu_startup_cx(struct acpi_cpu_softc *sc)
{
    acpi_cpu_cx_list(sc);
    
    SYSCTL_ADD_STRING(&sc->cpu_sysctl_ctx,
		      SYSCTL_CHILDREN(device_get_sysctl_tree(sc->cpu_dev)),
		      OID_AUTO, "cx_supported", CTLFLAG_RD,
		      sc->cpu_cx_supported, 0,
		      "Cx/microsecond values for supported Cx states");
    SYSCTL_ADD_PROC(&sc->cpu_sysctl_ctx,
		    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->cpu_dev)),
		    OID_AUTO, "cx_lowest", CTLTYPE_STRING | CTLFLAG_RW,
		    (void *)sc, 0, acpi_cpu_cx_lowest_sysctl, "A",
		    "lowest Cx sleep state to use");
    SYSCTL_ADD_PROC(&sc->cpu_sysctl_ctx,
		    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->cpu_dev)),
		    OID_AUTO, "cx_usage", CTLTYPE_STRING | CTLFLAG_RD,
		    (void *)sc, 0, acpi_cpu_usage_sysctl, "A",
		    "percent usage for each Cx state");
    SYSCTL_ADD_PROC(&sc->cpu_sysctl_ctx,
		    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->cpu_dev)),
		    OID_AUTO, "cx_usage_counters", CTLTYPE_STRING | CTLFLAG_RD,
		    (void *)sc, 0, acpi_cpu_usage_counters_sysctl, "A",
		    "Cx sleep state counters");
#if defined(__i386__) || defined(__amd64__)
    SYSCTL_ADD_PROC(&sc->cpu_sysctl_ctx,
		    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->cpu_dev)),
		    OID_AUTO, "cx_method", CTLTYPE_STRING | CTLFLAG_RD,
		    (void *)sc, 0, acpi_cpu_method_sysctl, "A",
		    "Cx entrance methods");
#endif

    /* Signal platform that we can handle _CST notification. */
    if (!cpu_cx_generic && cpu_cst_cnt != 0) {
	ACPI_LOCK(acpi);
	AcpiOsWritePort(cpu_smi_cmd, cpu_cst_cnt, 8);
	ACPI_UNLOCK(acpi);
    }
}