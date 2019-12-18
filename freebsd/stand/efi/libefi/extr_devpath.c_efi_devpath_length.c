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
typedef  scalar_t__ UINTN ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 scalar_t__ DevicePathNodeLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsDevicePathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NextDevicePathNode (int /*<<< orphan*/ *) ; 

UINTN
efi_devpath_length(EFI_DEVICE_PATH  *path)
{
	EFI_DEVICE_PATH *start = path;

	while (!IsDevicePathEnd(path))
		path = NextDevicePathNode(path);
	return ((UINTN)path - (UINTN)start) + DevicePathNodeLength(path);
}