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
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 size_t DevicePathNodeLength (int /*<<< orphan*/ *) ; 
 scalar_t__ DevicePathSubType (int /*<<< orphan*/ *) ; 
 scalar_t__ DevicePathType (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

bool
efi_devpath_match_node(EFI_DEVICE_PATH *devpath1, EFI_DEVICE_PATH *devpath2)
{
	size_t len;

	if (devpath1 == NULL || devpath2 == NULL)
		return (false);
	if (DevicePathType(devpath1) != DevicePathType(devpath2) ||
	    DevicePathSubType(devpath1) != DevicePathSubType(devpath2))
		return (false);
	len = DevicePathNodeLength(devpath1);
	if (len != DevicePathNodeLength(devpath2))
		return (false);
	if (memcmp(devpath1, devpath2, len) != 0)
		return (false);
	return (true);
}