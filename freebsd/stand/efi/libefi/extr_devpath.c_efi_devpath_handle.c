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
struct TYPE_2__ {int /*<<< orphan*/  (* LocateDevicePath ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/ * EFI_HANDLE ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 TYPE_1__* BS ; 
 int /*<<< orphan*/  DevicePathGUID ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

EFI_HANDLE
efi_devpath_handle(EFI_DEVICE_PATH *devpath)
{
	EFI_STATUS status;
	EFI_HANDLE h;

	/*
	 * There isn't a standard way to locate a handle for a given
	 * device path.  However, querying the EFI_DEVICE_PATH protocol
	 * for a given device path should give us a handle for the
	 * closest node in the path to the end that is valid.
	 */
	status = BS->LocateDevicePath(&DevicePathGUID, &devpath, &h);
	if (EFI_ERROR(status))
		return (NULL);
	return (h);
}