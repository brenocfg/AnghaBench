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
struct TYPE_3__ {int /*<<< orphan*/ * (* ConvertTextToDevicePath ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 TYPE_2__* BS ; 
 int /*<<< orphan*/  DevicePathFromTextGUID ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_1__* fromTextProtocol ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *) ; 

EFI_DEVICE_PATH *
efi_name_to_devpath16(CHAR16 *path)
{
	EFI_STATUS status;

	if (path == NULL)
		return (NULL);
	if (fromTextProtocol == NULL) {
		status = BS->LocateProtocol(&DevicePathFromTextGUID, NULL,
		    (VOID **)&fromTextProtocol);
		if (EFI_ERROR(status))
			fromTextProtocol = NULL;
	}
	if (fromTextProtocol == NULL)
		return (NULL);

	return (fromTextProtocol->ConvertTextToDevicePath(path));
}