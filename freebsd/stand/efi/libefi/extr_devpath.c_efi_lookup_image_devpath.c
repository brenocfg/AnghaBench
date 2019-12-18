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
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageDevicePathGUID ; 
 int /*<<< orphan*/  OpenProtocolByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

EFI_DEVICE_PATH *
efi_lookup_image_devpath(EFI_HANDLE handle)
{
	EFI_DEVICE_PATH *devpath;
	EFI_STATUS status;

	status = OpenProtocolByHandle(handle, &ImageDevicePathGUID,
	    (void **)&devpath);
	if (EFI_ERROR(status))
		devpath = NULL;
	return (devpath);
}