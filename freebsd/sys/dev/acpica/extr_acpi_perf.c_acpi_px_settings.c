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
struct acpi_perf_softc {int px_count; int px_max_avail; int /*<<< orphan*/ * px_states; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_px_to_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cf_setting*) ; 
 struct acpi_perf_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_px_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct acpi_perf_softc *sc;
	int x, y;

	sc = device_get_softc(dev);
	if (sets == NULL || count == NULL)
		return (EINVAL);
	if (*count < sc->px_count - sc->px_max_avail)
		return (E2BIG);

	/* Return a list of settings that are currently valid. */
	y = 0;
	for (x = sc->px_max_avail; x < sc->px_count; x++, y++)
		acpi_px_to_set(dev, &sc->px_states[x], &sets[y]);
	*count = sc->px_count - sc->px_max_avail;

	return (0);
}