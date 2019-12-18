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
struct bhnd_core_info {uintptr_t vendor; uintptr_t device; uintptr_t hwrev; uintptr_t core_idx; uintptr_t unit; } ;
struct bcma_devinfo {int /*<<< orphan*/  pmu_info; TYPE_1__* corecfg; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct bhnd_core_info core_info; } ;

/* Variables and functions */
#define  BHND_IVAR_CORE_INDEX 136 
#define  BHND_IVAR_CORE_UNIT 135 
#define  BHND_IVAR_DEVICE 134 
#define  BHND_IVAR_DEVICE_CLASS 133 
#define  BHND_IVAR_DEVICE_NAME 132 
#define  BHND_IVAR_HWREV 131 
#define  BHND_IVAR_PMU_INFO 130 
#define  BHND_IVAR_VENDOR 129 
#define  BHND_IVAR_VENDOR_NAME 128 
 int ENOENT ; 
 uintptr_t bhnd_core_class (struct bhnd_core_info const*) ; 
 int /*<<< orphan*/  bhnd_core_name (struct bhnd_core_info const*) ; 
 int /*<<< orphan*/  bhnd_vendor_name (uintptr_t) ; 
 struct bcma_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcma_read_ivar(device_t dev, device_t child, int index, uintptr_t *result)
{
	const struct bcma_devinfo *dinfo;
	const struct bhnd_core_info *ci;
	
	dinfo = device_get_ivars(child);
	ci = &dinfo->corecfg->core_info;
	
	switch (index) {
	case BHND_IVAR_VENDOR:
		*result = ci->vendor;
		return (0);
	case BHND_IVAR_DEVICE:
		*result = ci->device;
		return (0);
	case BHND_IVAR_HWREV:
		*result = ci->hwrev;
		return (0);
	case BHND_IVAR_DEVICE_CLASS:
		*result = bhnd_core_class(ci);
		return (0);
	case BHND_IVAR_VENDOR_NAME:
		*result = (uintptr_t) bhnd_vendor_name(ci->vendor);
		return (0);
	case BHND_IVAR_DEVICE_NAME:
		*result = (uintptr_t) bhnd_core_name(ci);
		return (0);
	case BHND_IVAR_CORE_INDEX:
		*result = ci->core_idx;
		return (0);
	case BHND_IVAR_CORE_UNIT:
		*result = ci->unit;
		return (0);
	case BHND_IVAR_PMU_INFO:
		*result = (uintptr_t) dinfo->pmu_info;
		return (0);
	default:
		return (ENOENT);
	}
}