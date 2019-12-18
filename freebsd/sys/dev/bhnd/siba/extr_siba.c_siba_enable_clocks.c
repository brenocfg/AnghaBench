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
typedef  int uint32_t ;
struct siba_softc {int dummy; } ;
struct siba_devinfo {int pmu_state; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int BHND_CLOCK_ALP ; 
 int BHND_CLOCK_DYN ; 
 int BHND_CLOCK_HT ; 
 int BHND_CLOCK_ILP ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  SIBA_LOCK (struct siba_softc*) ; 
#define  SIBA_PMU_BHND 131 
#define  SIBA_PMU_FIXED 130 
#define  SIBA_PMU_NONE 129 
#define  SIBA_PMU_PWRCTL 128 
 int /*<<< orphan*/  SIBA_UNLOCK (struct siba_softc*) ; 
 int bhnd_generic_enable_clocks (scalar_t__,scalar_t__,int) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct siba_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static int
siba_enable_clocks(device_t dev, device_t child, uint32_t clocks)
{
	struct siba_softc	*sc;
	struct siba_devinfo	*dinfo;

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
		return (bhnd_generic_enable_clocks(dev, child, clocks));

	case SIBA_PMU_PWRCTL:
	case SIBA_PMU_FIXED:
		SIBA_UNLOCK(sc);

		/* All (supported) clocks are already enabled by default */
		clocks &= ~(BHND_CLOCK_DYN |
			    BHND_CLOCK_ILP |
			    BHND_CLOCK_ALP |
			    BHND_CLOCK_HT);

		if (clocks != 0) {
			device_printf(dev, "%s requested unknown clocks: %#x\n",
			    device_get_nameunit(child), clocks);
			return (ENODEV);
		}

		return (0);
	}

	panic("invalid PMU state: %d", dinfo->pmu_state);
}