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
 scalar_t__ IsDevicePathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NextDevicePathNode (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

bool
efi_devpath_is_prefix(EFI_DEVICE_PATH *prefix, EFI_DEVICE_PATH *path)
{
	size_t len;

	if (prefix == NULL || path == NULL)
		return (false);

	while (1) {
		if (IsDevicePathEnd(prefix))
			break;

		if (DevicePathType(prefix) != DevicePathType(path) ||
		    DevicePathSubType(prefix) != DevicePathSubType(path))
			return (false);

		len = DevicePathNodeLength(prefix);
		if (len != DevicePathNodeLength(path))
			return (false);

		if (memcmp(prefix, path, len) != 0)
			return (false);

		prefix = NextDevicePathNode(prefix);
		path = NextDevicePathNode(path);
	}
	return (true);
}