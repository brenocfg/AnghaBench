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
struct siba_devinfo {scalar_t__ pmu_state; TYPE_1__ pmu; } ;
struct chipc_caps {scalar_t__ pwr_ctrl; scalar_t__ pmu; } ;
typedef  scalar_t__ siba_pmu_state ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  ccaps ;

/* Variables and functions */
 struct chipc_caps* BHND_CHIPC_GET_CAPS (scalar_t__) ; 
 int /*<<< orphan*/  BHND_SERVICE_CHIPC ; 
 int /*<<< orphan*/  BHND_SERVICE_PWRCTL ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SIBA_LOCK (struct siba_softc*) ; 
 scalar_t__ SIBA_PMU_BHND ; 
 scalar_t__ SIBA_PMU_FIXED ; 
 scalar_t__ SIBA_PMU_NONE ; 
 scalar_t__ SIBA_PMU_PWRCTL ; 
 int /*<<< orphan*/  SIBA_UNLOCK (struct siba_softc*) ; 
 int bhnd_generic_alloc_pmu (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bhnd_release_provider (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_retain_provider (scalar_t__,int /*<<< orphan*/ ) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct siba_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*) ; 
 int /*<<< orphan*/  memset (struct chipc_caps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siba_alloc_pmu(device_t dev, device_t child)
{
	struct siba_softc	*sc;
	struct siba_devinfo	*dinfo;
	device_t		 chipc;
	device_t		 pwrctl;
	struct chipc_caps	 ccaps;
	siba_pmu_state		 pmu_state;
	int			 error;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	sc = device_get_softc(dev);
	dinfo = device_get_ivars(child);
	pwrctl = NULL;

	/* Fetch ChipCommon capability flags */
	chipc = bhnd_retain_provider(child, BHND_SERVICE_CHIPC);
	if (chipc != NULL) {
		ccaps = *BHND_CHIPC_GET_CAPS(chipc);
		bhnd_release_provider(child, chipc, BHND_SERVICE_CHIPC);
	} else {
		memset(&ccaps, 0, sizeof(ccaps));
	}

	/* Defer to bhnd(4)'s PMU implementation if ChipCommon exists and
	 * advertises PMU support */
	if (ccaps.pmu) {
		if ((error = bhnd_generic_alloc_pmu(dev, child)))
			return (error);

		KASSERT(dinfo->pmu_state == SIBA_PMU_BHND,
		    ("unexpected PMU state: %d", dinfo->pmu_state));

		return (0);
	}

	/*
	 * This is either a legacy PWRCTL chipset, or the device does not
	 * support dynamic clock control.
	 * 
	 * We need to map all bhnd(4) bus PMU to PWRCTL or no-op operations.
	 */
	if (ccaps.pwr_ctrl) {
		pmu_state = SIBA_PMU_PWRCTL;
		pwrctl = bhnd_retain_provider(child, BHND_SERVICE_PWRCTL);
		if (pwrctl == NULL) {
			device_printf(dev, "PWRCTL not found\n");
			return (ENODEV);
		}
	} else {
		pmu_state = SIBA_PMU_FIXED;
		pwrctl = NULL;
	}

	SIBA_LOCK(sc);

	/* Per-core PMU state already allocated? */
	if (dinfo->pmu_state != SIBA_PMU_NONE) {
		panic("duplicate PMU allocation for %s",
		    device_get_nameunit(child));
	}

	/* Update the child's PMU allocation state, and transfer ownership of
	 * the PWRCTL provider reference (if any) */
	dinfo->pmu_state = pmu_state;
	dinfo->pmu.pwrctl = pwrctl;

	SIBA_UNLOCK(sc);

	return (0);
}