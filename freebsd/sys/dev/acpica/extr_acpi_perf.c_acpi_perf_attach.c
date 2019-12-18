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
struct acpi_perf_softc {int /*<<< orphan*/  info_only; int /*<<< orphan*/  px_curr_state; scalar_t__ px_max_avail; int /*<<< orphan*/  handle; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int ENXIO ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_perf_evaluate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_px_startup ; 
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 struct acpi_perf_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_perf_attach(device_t dev)
{
	struct acpi_perf_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->handle = acpi_get_handle(dev);
	sc->px_max_avail = 0;
	sc->px_curr_state = CPUFREQ_VAL_UNKNOWN;
	if (acpi_perf_evaluate(dev) != 0)
		return (ENXIO);
	AcpiOsExecute(OSL_NOTIFY_HANDLER, acpi_px_startup, NULL);
	if (!sc->info_only)
		cpufreq_register(dev);

	return (0);
}