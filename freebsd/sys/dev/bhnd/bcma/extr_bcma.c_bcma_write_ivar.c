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
struct bcma_devinfo {void* pmu_info; } ;
typedef  int /*<<< orphan*/  device_t ;

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
 int EINVAL ; 
 int ENOENT ; 
 struct bcma_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcma_write_ivar(device_t dev, device_t child, int index, uintptr_t value)
{
	struct bcma_devinfo *dinfo;

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
		dinfo->pmu_info = (void *)value;
		return (0);
	default:
		return (ENOENT);
	}
}