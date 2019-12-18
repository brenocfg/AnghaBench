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
struct TYPE_2__ {void* bhnd_info; } ;
struct siba_devinfo {int pmu_state; TYPE_1__ pmu; } ;
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
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  SIBA_LOCK (struct siba_softc*) ; 
#define  SIBA_PMU_BHND 131 
#define  SIBA_PMU_FIXED 130 
#define  SIBA_PMU_NONE 129 
#define  SIBA_PMU_PWRCTL 128 
 int /*<<< orphan*/  SIBA_UNLOCK (struct siba_softc*) ; 
 struct siba_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct siba_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
siba_write_ivar(device_t dev, device_t child, int index, uintptr_t value)
{
	struct siba_softc	*sc;
	struct siba_devinfo	*dinfo;

	sc = device_get_softc(dev);
	dinfo = device_get_ivars(child);

	switch (index) {
	case BHND_IVAR_VENDOR:
	case BHND_IVAR_DEVICE:
	case BHND_IVAR_HWREV:
	case BHND_IVAR_DEVICE_CLASS:
	case BHND_IVAR_VENDOR_NAME:
	case BHND_IVAR_DEVICE_NAME:
	case BHND_IVAR_CORE_INDEX:
	case BHND_IVAR_CORE_UNIT:
		return (EINVAL);
	case BHND_IVAR_PMU_INFO:
		SIBA_LOCK(sc);
		switch (dinfo->pmu_state) {
		case SIBA_PMU_NONE:
		case SIBA_PMU_BHND:
			dinfo->pmu.bhnd_info = (void *)value;
			dinfo->pmu_state = SIBA_PMU_BHND;
			SIBA_UNLOCK(sc);
			return (0);

		case SIBA_PMU_PWRCTL:
		case SIBA_PMU_FIXED:
			panic("bhnd_set_pmu_info() called with siba PMU state "
			    "%d", dinfo->pmu_state);
			return (ENXIO);
		}

		panic("invalid PMU state: %d", dinfo->pmu_state);
		return (ENXIO);

	default:
		return (ENOENT);
	}
}