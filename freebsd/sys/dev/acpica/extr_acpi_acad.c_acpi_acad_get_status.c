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
struct acpi_acad_softc {int status; } ;
typedef  void* device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_VPRINT (void*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  POWER_PROFILE_ECONOMY ; 
 int /*<<< orphan*/  POWER_PROFILE_PERFORMANCE ; 
 int /*<<< orphan*/  acad ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  acpi_UserNotify (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (void*) ; 
 int /*<<< orphan*/  acpi_get_handle (void*) ; 
 struct acpi_acad_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  power_profile_set_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_acad_get_status(void *context)
{
    struct acpi_acad_softc *sc;
    device_t	dev;
    ACPI_HANDLE	h;
    int		newstatus;

    dev = context;
    sc = device_get_softc(dev);
    h = acpi_get_handle(dev);
    newstatus = -1;
    acpi_GetInteger(h, "_PSR", &newstatus);

    /* If status is valid and has changed, notify the system. */
    ACPI_SERIAL_BEGIN(acad);
    if (newstatus != -1 && sc->status != newstatus) {
	sc->status = newstatus;
	ACPI_SERIAL_END(acad);
	power_profile_set_state(newstatus ? POWER_PROFILE_PERFORMANCE :
	    POWER_PROFILE_ECONOMY);
	ACPI_VPRINT(dev, acpi_device_get_parent_softc(dev),
	    "%s Line\n", newstatus ? "On" : "Off");
	acpi_UserNotify("ACAD", h, newstatus);
    } else
	ACPI_SERIAL_END(acad);
}