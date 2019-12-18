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
typedef  int /*<<< orphan*/  u_int ;
struct siba_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pwrctl; } ;
struct siba_devinfo {int pmu_state; TYPE_1__ pmu; } ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  bhnd_clock ;

/* Variables and functions */
#define  BHND_CLOCK_HT 132 
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  SIBA_LOCK (struct siba_softc*) ; 
#define  SIBA_PMU_BHND 131 
#define  SIBA_PMU_FIXED 130 
#define  SIBA_PMU_NONE 129 
#define  SIBA_PMU_PWRCTL 128 
 int /*<<< orphan*/  SIBA_UNLOCK (struct siba_softc*) ; 
 int bhnd_generic_get_clock_latency (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bhnd_pwrctl_get_clock_latency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct siba_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static int
siba_get_clock_latency(device_t dev, device_t child, bhnd_clock clock,
    u_int *latency)
{
	struct siba_softc	*sc;
	struct siba_devinfo	*dinfo;
	int			 error;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	sc = device_get_softc(dev);
	dinfo = device_get_ivars(child);

	SIBA_LOCK(sc);
	switch(dinfo->pmu_state) {
	case SIBA_PMU_NONE:
		panic("no active PMU request state");

		SIBA_UNLOCK(sc);
		return (ENXIO);

	case SIBA_PMU_BHND:
		SIBA_UNLOCK(sc);
		return (bhnd_generic_get_clock_latency(dev, child, clock,
		    latency));

	case SIBA_PMU_PWRCTL:
		 error = bhnd_pwrctl_get_clock_latency(dinfo->pmu.pwrctl, clock,
		    latency);
		 SIBA_UNLOCK(sc);

		 return (error);

	case SIBA_PMU_FIXED:
		SIBA_UNLOCK(sc);

		/* HT clock is always available, and incurs no transition
		 * delay. */
		switch (clock) {
		case BHND_CLOCK_HT:
			*latency = 0;
			return (0);

		default:
			return (ENODEV);
		}

		return (ENODEV);
	}

	panic("invalid PMU state: %d", dinfo->pmu_state);
}