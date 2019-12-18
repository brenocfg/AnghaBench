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
typedef  int /*<<< orphan*/  u_int ;
struct bhnd_pmu_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bhnd_clock ;

/* Variables and functions */
#define  BHND_CLOCK_HT 128 
 int /*<<< orphan*/  BPMU_LOCK (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  BPMU_UNLOCK (struct bhnd_pmu_softc*) ; 
 int ENODEV ; 
 int bhnd_pmu_fast_pwrup_delay (struct bhnd_pmu_softc*,int /*<<< orphan*/ *) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_pmu_get_clock_latency_method(device_t dev, bhnd_clock clock,
    u_int *latency)
{
	struct bhnd_pmu_softc	*sc;
	u_int			 pwrup_delay;
	int			 error;

	sc = device_get_softc(dev);

	switch (clock) {
	case BHND_CLOCK_HT:
		BPMU_LOCK(sc);
		error = bhnd_pmu_fast_pwrup_delay(sc, &pwrup_delay);
		BPMU_UNLOCK(sc);

		if (error)
			return (error);

		*latency = pwrup_delay;
		return (0);

	default:
		return (ENODEV);
	}
}