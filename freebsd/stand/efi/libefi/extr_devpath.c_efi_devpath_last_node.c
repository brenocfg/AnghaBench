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
 scalar_t__ IsDevicePathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NextDevicePathNode (int /*<<< orphan*/ *) ; 

EFI_DEVICE_PATH *
efi_devpath_last_node(EFI_DEVICE_PATH *devpath)
{

	if (IsDevicePathEnd(devpath))
		return (NULL);
	while (!IsDevicePathEnd(NextDevicePathNode(devpath)))
		devpath = NextDevicePathNode(devpath);
	return (devpath);
}