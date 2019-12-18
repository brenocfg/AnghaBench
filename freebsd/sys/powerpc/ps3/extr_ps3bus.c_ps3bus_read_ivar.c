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
struct ps3bus_devinfo {uintptr_t bus; uintptr_t dev; uintptr_t bustype; uintptr_t devtype; uintptr_t busidx; uintptr_t devidx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PS3BUS_IVAR_BUS 133 
#define  PS3BUS_IVAR_BUSIDX 132 
#define  PS3BUS_IVAR_BUSTYPE 131 
#define  PS3BUS_IVAR_DEVICE 130 
#define  PS3BUS_IVAR_DEVIDX 129 
#define  PS3BUS_IVAR_DEVTYPE 128 
 struct ps3bus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ps3bus_read_ivar(device_t bus, device_t child, int which, uintptr_t *result)
{
	struct ps3bus_devinfo *dinfo = device_get_ivars(child);

	switch (which) {
	case PS3BUS_IVAR_BUS:
		*result = dinfo->bus;
		break;
	case PS3BUS_IVAR_DEVICE:
		*result = dinfo->dev;
		break;
	case PS3BUS_IVAR_BUSTYPE:
		*result = dinfo->bustype;
		break;
	case PS3BUS_IVAR_DEVTYPE:
		*result = dinfo->devtype;
		break;
	case PS3BUS_IVAR_BUSIDX:
		*result = dinfo->busidx;
		break;
	case PS3BUS_IVAR_DEVIDX:
		*result = dinfo->devidx;
		break;
	default:
		return (EINVAL);
	}

	return (0);
}