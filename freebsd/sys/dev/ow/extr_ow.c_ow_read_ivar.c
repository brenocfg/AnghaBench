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
struct ow_devinfo {int romid; } ;
typedef  int romid_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  OW_IVAR_FAMILY 129 
#define  OW_IVAR_ROMID 128 
 struct ow_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ow_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct ow_devinfo *di;
	romid_t **ptr;

	di = device_get_ivars(child);
	switch (which) {
	case OW_IVAR_FAMILY:
		*result = di->romid & 0xff;
		break;
	case OW_IVAR_ROMID:
		ptr = (romid_t **)result;
		*ptr = &di->romid;
		break;
	default:
		return EINVAL;
	}

	return 0;
}