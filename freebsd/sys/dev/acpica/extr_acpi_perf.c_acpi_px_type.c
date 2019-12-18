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
struct acpi_perf_softc {scalar_t__ info_only; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CPUFREQ_FLAG_INFO_ONLY ; 
 int CPUFREQ_TYPE_ABSOLUTE ; 
 int EINVAL ; 
 struct acpi_perf_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_px_type(device_t dev, int *type)
{
	struct acpi_perf_softc *sc;

	if (type == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);

	*type = CPUFREQ_TYPE_ABSOLUTE;
	if (sc->info_only)
		*type |= CPUFREQ_FLAG_INFO_ONLY;
	return (0);
}