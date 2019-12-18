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
struct siba_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ pwrctl; } ;
struct siba_devinfo {int pmu_state; TYPE_1__ pmu; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CLOCK_DYN ; 
 int /*<<< orphan*/  BHND_SERVICE_PWRCTL ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SIBA_LOCK (struct siba_softc*) ; 
#define  SIBA_PMU_BHND 131 
#define  SIBA_PMU_FIXED 130 
#define  SIBA_PMU_NONE 129 
#define  SIBA_PMU_PWRCTL 128 
 int /*<<< orphan*/  SIBA_UNLOCK (struct siba_softc*) ; 
 int bhnd_generic_release_pmu (scalar_t__,scalar_t__) ; 
 int bhnd_pwrctl_request_clock (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_release_provider (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 int device_get_nameunit (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct siba_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
siba_release_pmu(device_t dev, device_t child)
{
	struct siba_softc	*sc;
	struct siba_devinfo	*dinfo;
	device_t		 pwrctl;
	int			 error;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	sc = device_get_softc(dev);
	dinfo = device_get_ivars(child);

	SIBA_LOCK(sc);
	switch(dinfo->pmu_state) {
	case SIBA_PMU_NONE:
		panic("pmu over-release for %s", device_get_nameunit(child));
		SIBA_UNLOCK(sc);
		return (ENXIO);

	case SIBA_PMU_BHND:
		SIBA_UNLOCK(sc);
		return (bhnd_generic_release_pmu(dev, child));

	case SIBA_PMU_PWRCTL:
		/* Requesting BHND_CLOCK_DYN releases any outstanding clock
		 * reservations */
		pwrctl = dinfo->pmu.pwrctl;
		error = bhnd_pwrctl_request_clock(pwrctl, child,
		    BHND_CLOCK_DYN);
		if (error) {
			SIBA_UNLOCK(sc);
			return (error);
		}

		/* Clean up the child's PMU state */
		dinfo->pmu_state = SIBA_PMU_NONE;
		dinfo->pmu.pwrctl = NULL;
		SIBA_UNLOCK(sc);

		/* Release the provider reference */
		bhnd_release_provider(child, pwrctl, BHND_SERVICE_PWRCTL);
		return (0);

	case SIBA_PMU_FIXED:
		/* Clean up the child's PMU state */
		KASSERT(dinfo->pmu.pwrctl == NULL,
		    ("PWRCTL reference with FIXED state"));

		dinfo->pmu_state = SIBA_PMU_NONE;
		dinfo->pmu.pwrctl = NULL;
		SIBA_UNLOCK(sc);
	}

	panic("invalid PMU state: %d", dinfo->pmu_state);
}