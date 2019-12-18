#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  (* LocateProtocol ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;
struct TYPE_3__ {int /*<<< orphan*/ * (* ConvertDevicePathToText ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 TYPE_2__* BS ; 
 int /*<<< orphan*/  DevicePathToTextGUID ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * efi_devpath_to_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* toTextProtocol ; 

CHAR16 *
efi_devpath_name(EFI_DEVICE_PATH *devpath)
{
	EFI_STATUS status;

	if (devpath == NULL)
		return (NULL);
	if (toTextProtocol == NULL) {
		status = BS->LocateProtocol(&DevicePathToTextGUID, NULL,
		    (VOID **)&toTextProtocol);
		if (EFI_ERROR(status))
			toTextProtocol = NULL;
	}
	if (toTextProtocol == NULL)
		return (efi_devpath_to_name(devpath));

	return (toTextProtocol->ConvertDevicePathToText(devpath, TRUE, TRUE));
}