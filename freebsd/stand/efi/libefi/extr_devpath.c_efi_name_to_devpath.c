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
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 int /*<<< orphan*/ * efi_name_to_devpath16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ utf8_to_ucs2 (char const*,int /*<<< orphan*/ **,size_t*) ; 

EFI_DEVICE_PATH *
efi_name_to_devpath(const char *path)
{
	EFI_DEVICE_PATH *devpath;
	CHAR16 *uv;
	size_t ul;

	uv = NULL;
	if (utf8_to_ucs2(path, &uv, &ul) != 0)
		return (NULL);
	devpath = efi_name_to_devpath16(uv);
	free(uv);
	return (devpath);
}