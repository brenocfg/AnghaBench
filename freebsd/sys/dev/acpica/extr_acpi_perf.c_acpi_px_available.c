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
struct cf_setting {int dummy; } ;
struct acpi_perf_softc {scalar_t__ px_max_avail; scalar_t__ px_curr_state; int /*<<< orphan*/  dev; int /*<<< orphan*/ * px_states; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ CPUFREQ_VAL_UNKNOWN ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_px_set (int /*<<< orphan*/ ,struct cf_setting*) ; 
 int /*<<< orphan*/  acpi_px_to_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cf_setting*) ; 

__attribute__((used)) static void
acpi_px_available(struct acpi_perf_softc *sc)
{
	ACPI_STATUS status;
	struct cf_setting set;

	status = acpi_GetInteger(sc->handle, "_PPC", &sc->px_max_avail);

	/* If the old state is too high, set current state to the new max. */
	if (ACPI_SUCCESS(status)) {
		if (sc->px_curr_state != CPUFREQ_VAL_UNKNOWN &&
		    sc->px_curr_state > sc->px_max_avail) {
			acpi_px_to_set(sc->dev,
			    &sc->px_states[sc->px_max_avail], &set);
			acpi_px_set(sc->dev, &set);
		}
	} else
		sc->px_max_avail = 0;
}