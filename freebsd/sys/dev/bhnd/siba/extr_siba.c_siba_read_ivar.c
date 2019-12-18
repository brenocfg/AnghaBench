#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct siba_softc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bhnd_info; } ;
struct bhnd_core_info {uintptr_t vendor; uintptr_t device; uintptr_t hwrev; uintptr_t core_idx; uintptr_t unit; } ;
struct TYPE_3__ {struct bhnd_core_info core_info; } ;
struct siba_devinfo {int /*<<< orphan*/  pmu_state; TYPE_2__ pmu; TYPE_1__ core_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BHND_IVAR_CORE_INDEX 140 
#define  BHND_IVAR_CORE_UNIT 139 
#define  BHND_IVAR_DEVICE 138 
#define  BHND_IVAR_DEVICE_CLASS 137 
#define  BHND_IVAR_DEVICE_NAME 136 
#define  BHND_IVAR_HWREV 135 
#define  BHND_IVAR_PMU_INFO 134 
#define  BHND_IVAR_VENDOR 133 
#define  BHND_IVAR_VENDOR_NAME 132 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  SIBA_LOCK (struct siba_softc*) ; 
#define  SIBA_PMU_BHND 131 
#define  SIBA_PMU_FIXED 130 
#define  SIBA_PMU_NONE 129 
#define  SIBA_PMU_PWRCTL 128 
 int /*<<< orphan*/  SIBA_UNLOCK (struct siba_softc*) ; 
 uintptr_t bhnd_core_class (struct bhnd_core_info const*) ; 
 int /*<<< orphan*/  bhnd_core_name (struct bhnd_core_info const*) ; 
 int /*<<< orphan*/  bhnd_vendor_name (uintptr_t) ; 
 struct siba_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct siba_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siba_read_ivar(device_t dev, device_t child, int index, uintptr_t *result)
{
	struct siba_softc		*sc;
	const struct siba_devinfo	*dinfo;
	const struct bhnd_core_info	*cfg;

	sc = device_get_softc(dev);
	dinfo = device_get_ivars(child);
	cfg = &dinfo->core_id.core_info;
	
	switch (index) {
	case BHND_IVAR_VENDOR:
		*result = cfg->vendor;
		return (0);
	case BHND_IVAR_DEVICE:
		*result = cfg->device;
		return (0);
	case BHND_IVAR_HWREV:
		*result = cfg->hwrev;
		return (0);
	case BHND_IVAR_DEVICE_CLASS:
		*result = bhnd_core_class(cfg);
		return (0);
	case BHND_IVAR_VENDOR_NAME:
		*result = (uintptr_t) bhnd_vendor_name(cfg->vendor);
		return (0);
	case BHND_IVAR_DEVICE_NAME:
		*result = (uintptr_t) bhnd_core_name(cfg);
		return (0);
	case BHND_IVAR_CORE_INDEX:
		*result = cfg->core_idx;
		return (0);
	case BHND_IVAR_CORE_UNIT:
		*result = cfg->unit;
		return (0);
	case BHND_IVAR_PMU_INFO:
		SIBA_LOCK(sc);
		switch (dinfo->pmu_state) {
		case SIBA_PMU_NONE:
			*result = (uintptr_t)NULL;
			SIBA_UNLOCK(sc);
			return (0);

		case SIBA_PMU_BHND:
			*result = (uintptr_t)dinfo->pmu.bhnd_info;
			SIBA_UNLOCK(sc);
			return (0);

		case SIBA_PMU_PWRCTL:
		case SIBA_PMU_FIXED:
			*result = (uintptr_t)NULL;
			SIBA_UNLOCK(sc);
			return (0);
		}

		panic("invalid PMU state: %d", dinfo->pmu_state);
		return (ENXIO);

	default:
		return (ENOENT);
	}
}