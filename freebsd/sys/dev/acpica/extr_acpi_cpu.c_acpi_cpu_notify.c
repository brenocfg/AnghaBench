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
struct acpi_cpu_softc {int /*<<< orphan*/  cpu_handle; } ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_NOTIFY_CX_STATES ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_UserNotify (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_cpu_cx_cst (struct acpi_cpu_softc*) ; 
 int /*<<< orphan*/  acpi_cpu_cx_list (struct acpi_cpu_softc*) ; 
 int /*<<< orphan*/  acpi_cpu_set_cx_lowest (struct acpi_cpu_softc*) ; 
 int /*<<< orphan*/  cpu ; 
 int /*<<< orphan*/  disable_idle (struct acpi_cpu_softc*) ; 
 int /*<<< orphan*/  enable_idle (struct acpi_cpu_softc*) ; 

__attribute__((used)) static void
acpi_cpu_notify(ACPI_HANDLE h, UINT32 notify, void *context)
{
    struct acpi_cpu_softc *sc = (struct acpi_cpu_softc *)context;

    if (notify != ACPI_NOTIFY_CX_STATES)
	return;

    /*
     * C-state data for target CPU is going to be in flux while we execute
     * acpi_cpu_cx_cst, so disable entering acpi_cpu_idle.
     * Also, it may happen that multiple ACPI taskqueues may concurrently
     * execute notifications for the same CPU.  ACPI_SERIAL is used to
     * protect against that.
     */
    ACPI_SERIAL_BEGIN(cpu);
    disable_idle(sc);

    /* Update the list of Cx states. */
    acpi_cpu_cx_cst(sc);
    acpi_cpu_cx_list(sc);
    acpi_cpu_set_cx_lowest(sc);

    enable_idle(sc);
    ACPI_SERIAL_END(cpu);

    acpi_UserNotify("PROCESSOR", sc->cpu_handle, notify);
}