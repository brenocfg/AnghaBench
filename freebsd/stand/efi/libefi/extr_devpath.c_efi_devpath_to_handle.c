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
typedef  int /*<<< orphan*/ * EFI_HANDLE ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 int /*<<< orphan*/  efi_devpath_match_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * efi_devpath_to_media_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * efi_lookup_devpath (int /*<<< orphan*/ *) ; 

EFI_HANDLE
efi_devpath_to_handle(EFI_DEVICE_PATH *path, EFI_HANDLE *handles, unsigned nhandles)
{
	unsigned i;
	EFI_DEVICE_PATH *media, *devpath;
	EFI_HANDLE h;

	media = efi_devpath_to_media_path(path);
	if (media == NULL)
		return (NULL);
	for (i = 0; i < nhandles; i++) {
		h = handles[i];
		devpath = efi_lookup_devpath(h);
		if (devpath == NULL)
			continue;
		if (!efi_devpath_match_node(media, efi_devpath_to_media_path(devpath)))
			continue;
		return (h);
	}
	return (NULL);
}