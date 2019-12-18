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
struct acpi_tz_softc {int tz_flags; int /*<<< orphan*/  tz_handle; int /*<<< orphan*/  tz_dev; } ;
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_VPRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  AcpiFormatException (scalar_t__) ; 
 int POWER_PROFILE_ECONOMY ; 
 int POWER_PROFILE_PERFORMANCE ; 
 int /*<<< orphan*/  TZ_FLAG_GETSETTINGS ; 
 int TZ_FLAG_NO_SCP ; 
 scalar_t__ acpi_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tz_signal (struct acpi_tz_softc*,int /*<<< orphan*/ ) ; 
 int power_profile_get_state () ; 

__attribute__((used)) static void
acpi_tz_power_profile(void *arg)
{
    ACPI_STATUS			status;
    struct acpi_tz_softc	*sc = (struct acpi_tz_softc *)arg;
    int				state;

    state = power_profile_get_state();
    if (state != POWER_PROFILE_PERFORMANCE && state != POWER_PROFILE_ECONOMY)
	return;

    /* check that we haven't decided there's no _SCP method */
    if ((sc->tz_flags & TZ_FLAG_NO_SCP) == 0) {

	/* Call _SCP to set the new profile */
	status = acpi_SetInteger(sc->tz_handle, "_SCP",
	    (state == POWER_PROFILE_PERFORMANCE) ? 0 : 1);
	if (ACPI_FAILURE(status)) {
	    if (status != AE_NOT_FOUND)
		ACPI_VPRINT(sc->tz_dev,
			    acpi_device_get_parent_softc(sc->tz_dev),
			    "can't evaluate %s._SCP - %s\n",
			    acpi_name(sc->tz_handle),
			    AcpiFormatException(status));
	    sc->tz_flags |= TZ_FLAG_NO_SCP;
	} else {
	    /* We have to re-evaluate the entire zone now */
	    acpi_tz_signal(sc, TZ_FLAG_GETSETTINGS);
	}
    }
}