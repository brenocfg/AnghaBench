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
 scalar_t__ IsDevicePathType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIA_DEVICE_PATH ; 
 int /*<<< orphan*/ * NextDevicePathNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_devpath_match_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
_efi_devpath_match(EFI_DEVICE_PATH *devpath1, EFI_DEVICE_PATH *devpath2,
    bool ignore_media)
{

	if (devpath1 == NULL || devpath2 == NULL)
		return (false);

	while (true) {
		if (ignore_media &&
		    IsDevicePathType(devpath1, MEDIA_DEVICE_PATH) &&
		    IsDevicePathType(devpath2, MEDIA_DEVICE_PATH))
			return (true);
		if (!efi_devpath_match_node(devpath1, devpath2))
			return false;
		if (IsDevicePathEnd(devpath1))
			break;
		devpath1 = NextDevicePathNode(devpath1);
		devpath2 = NextDevicePathNode(devpath2);
	}
	return (true);
}