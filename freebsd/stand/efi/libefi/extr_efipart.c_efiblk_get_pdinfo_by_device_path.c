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
typedef  int /*<<< orphan*/  pdinfo_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* LocateDevicePath ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 TYPE_1__* BS ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkio_guid ; 
 int /*<<< orphan*/ * efiblk_get_pdinfo_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

pdinfo_t *
efiblk_get_pdinfo_by_device_path(EFI_DEVICE_PATH *path)
{
	EFI_HANDLE h;
	EFI_STATUS status;
	EFI_DEVICE_PATH *devp = path;

	status = BS->LocateDevicePath(&blkio_guid, &devp, &h);
	if (EFI_ERROR(status))
		return (NULL);
	return (efiblk_get_pdinfo_by_handle(h));
}