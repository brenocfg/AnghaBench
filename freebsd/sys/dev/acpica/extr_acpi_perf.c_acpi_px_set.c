#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cf_setting {int /*<<< orphan*/  freq; } ;
struct acpi_perf_softc {int px_max_avail; int px_count; int px_curr_state; TYPE_1__* px_states; int /*<<< orphan*/  perf_status; int /*<<< orphan*/  perf_ctrl; scalar_t__ info_only; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int sts_val; int /*<<< orphan*/  core_freq; int /*<<< orphan*/  ctrl_val; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int ENXIO ; 
 int PX_GET_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PX_SET_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_perf_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_px_set(device_t dev, const struct cf_setting *set)
{
	struct acpi_perf_softc *sc;
	int i, status, sts_val, tries;

	if (set == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);

	/* If we can't set new states, return immediately. */
	if (sc->info_only)
		return (ENXIO);

	/* Look up appropriate state, based on frequency. */
	for (i = sc->px_max_avail; i < sc->px_count; i++) {
		if (CPUFREQ_CMP(set->freq, sc->px_states[i].core_freq))
			break;
	}
	if (i == sc->px_count)
		return (EINVAL);

	/* Write the appropriate value to the register. */
	PX_SET_REG(sc->perf_ctrl, sc->px_states[i].ctrl_val);

	/*
	 * Try for up to 10 ms to verify the desired state was selected.
	 * This is longer than the standard says (1 ms) but in some modes,
	 * systems may take longer to respond.
	 */
	sts_val = sc->px_states[i].sts_val;
	for (tries = 0; tries < 1000; tries++) {
		status = PX_GET_REG(sc->perf_status);

		/*
		 * If we match the status or the desired status is 8 bits
		 * and matches the relevant bits, assume we succeeded.  It
		 * appears some systems (IBM R32) expect byte-wide access
		 * even though the standard says the register is 32-bit.
		 */
		if (status == sts_val ||
		    ((sts_val & ~0xff) == 0 && (status & 0xff) == sts_val))
			break;
		DELAY(10);
	}
	if (tries == 1000) {
		device_printf(dev, "Px transition to %d failed\n",
		    sc->px_states[i].core_freq);
		return (ENXIO);
	}
	sc->px_curr_state = i;

	return (0);
}