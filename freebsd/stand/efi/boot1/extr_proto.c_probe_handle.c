#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int preferred; int /*<<< orphan*/ * devdata; int /*<<< orphan*/ * next; int /*<<< orphan*/  devhandle; int /*<<< orphan*/ * devpath; TYPE_3__* dev; } ;
typedef  TYPE_2__ dev_info_t ;
typedef  size_t UINTN ;
struct TYPE_11__ {scalar_t__ (* probe ) (TYPE_2__*) ;} ;
struct TYPE_10__ {TYPE_1__* Media; } ;
struct TYPE_8__ {int /*<<< orphan*/  LogicalPartition; } ;
typedef  scalar_t__ EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;
typedef  TYPE_3__ EFI_BLOCK_IO ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 int /*<<< orphan*/  BlockIoProtocolGUID ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DevicePathGUID ; 
 int /*<<< orphan*/  EFI_ERROR_CODE (scalar_t__) ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ EFI_UNSUPPORTED ; 
 scalar_t__ OpenProtocolByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 TYPE_7__** boot_modules ; 
 int /*<<< orphan*/ * efi_devpath_name (int /*<<< orphan*/ *) ; 
 int efi_devpath_same_disk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_free_devpath_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 size_t num_boot_modules ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

__attribute__((used)) static int
probe_handle(EFI_HANDLE h, EFI_DEVICE_PATH *imgpath)
{
	dev_info_t *devinfo;
	EFI_BLOCK_IO *blkio;
	EFI_DEVICE_PATH *devpath;
	EFI_STATUS status;
	UINTN i;
	int preferred;

	/* Figure out if we're dealing with an actual partition. */
	status = OpenProtocolByHandle(h, &DevicePathGUID, (void **)&devpath);
	if (status == EFI_UNSUPPORTED)
		return (0);

	if (status != EFI_SUCCESS) {
		DPRINTF("\nFailed to query DevicePath (%lu)\n",
		    EFI_ERROR_CODE(status));
		return (-1);
	}
#ifdef EFI_DEBUG
	{
		CHAR16 *text = efi_devpath_name(devpath);
		DPRINTF("probing: %S ", text);
		efi_free_devpath_name(text);
	}
#endif
	status = OpenProtocolByHandle(h, &BlockIoProtocolGUID, (void **)&blkio);
	if (status == EFI_UNSUPPORTED)
		return (0);

	if (status != EFI_SUCCESS) {
		DPRINTF("\nFailed to query BlockIoProtocol (%lu)\n",
		    EFI_ERROR_CODE(status));
		return (-1);
	}

	if (!blkio->Media->LogicalPartition)
		return (0);

	preferred = efi_devpath_same_disk(imgpath, devpath);

	/* Run through each module, see if it can load this partition */
	devinfo = malloc(sizeof(*devinfo));
	if (devinfo == NULL) {
		DPRINTF("\nFailed to allocate devinfo\n");
		return (-1);
	}
	devinfo->dev = blkio;
	devinfo->devpath = devpath;
	devinfo->devhandle = h;
	devinfo->preferred = preferred;
	devinfo->next = NULL;

	for (i = 0; i < num_boot_modules; i++) {
		devinfo->devdata = NULL;

		status = boot_modules[i]->probe(devinfo);
		if (status == EFI_SUCCESS)
			return (preferred + 1);
	}
	free(devinfo);

	return (0);
}