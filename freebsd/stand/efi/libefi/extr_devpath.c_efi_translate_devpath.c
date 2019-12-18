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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
#define  ACPI_DEVICE_PATH 132 
#define  BBS_DEVICE_PATH 131 
 int DevicePathType (int /*<<< orphan*/ *) ; 
#define  HARDWARE_DEVICE_PATH 130 
 int /*<<< orphan*/  IsDevicePathEnd (int /*<<< orphan*/ *) ; 
#define  MEDIA_DEVICE_PATH 129 
#define  MESSAGING_DEVICE_PATH 128 
 int /*<<< orphan*/ * NextDevicePathNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int,char*) ; 
 char* efi_acpi_dev_path (int /*<<< orphan*/ *,char*) ; 
 char* efi_hw_dev_path (int /*<<< orphan*/ *,char*) ; 
 char* efi_media_dev_path (int /*<<< orphan*/ *,char*) ; 
 char* efi_messaging_dev_path (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static char *
efi_translate_devpath(EFI_DEVICE_PATH *devpath)
{
	EFI_DEVICE_PATH *dp = NextDevicePathNode(devpath);
	char *name, *ptr;
	uint8_t type;

	if (!IsDevicePathEnd(devpath))
		name = efi_translate_devpath(dp);
	else
		return (NULL);

	ptr = NULL;
	type = DevicePathType(devpath);
	switch (type) {
	case HARDWARE_DEVICE_PATH:
		ptr = efi_hw_dev_path(devpath, name);
		break;
	case ACPI_DEVICE_PATH:
		ptr = efi_acpi_dev_path(devpath, name);
		break;
	case MESSAGING_DEVICE_PATH:
		ptr = efi_messaging_dev_path(devpath, name);
		break;
	case MEDIA_DEVICE_PATH:
		ptr = efi_media_dev_path(devpath, name);
		break;
	case BBS_DEVICE_PATH:
	default:
		if (asprintf(&ptr, "UnknownPath(%x)%s", type,
		    name? name : "") < 0)
			ptr = NULL;
		break;
	}

	if (ptr != NULL) {
		free(name);
		name = ptr;
	}
	return (name);
}