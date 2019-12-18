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
struct acpi_tz_softc {int dummy; } ;

/* Variables and functions */
 int TZ_FLAG_GETPROFILE ; 
 int TZ_FLAG_GETSETTINGS ; 
 int /*<<< orphan*/  acpi_tz_establish (struct acpi_tz_softc*) ; 
 int /*<<< orphan*/  acpi_tz_monitor (struct acpi_tz_softc*) ; 
 int /*<<< orphan*/  acpi_tz_power_profile (struct acpi_tz_softc*) ; 

__attribute__((used)) static void
acpi_tz_timeout(struct acpi_tz_softc *sc, int flags)
{

    /* Check the current temperature and take action based on it */
    acpi_tz_monitor(sc);

    /* If requested, get the power profile settings. */
    if (flags & TZ_FLAG_GETPROFILE)
	acpi_tz_power_profile(sc);

    /*
     * If requested, check for new devices/setpoints.  After finding them,
     * check if we need to switch fans based on the new values.
     */
    if (flags & TZ_FLAG_GETSETTINGS) {
	acpi_tz_establish(sc);
	acpi_tz_monitor(sc);
    }

    /* XXX passive cooling actions? */
}