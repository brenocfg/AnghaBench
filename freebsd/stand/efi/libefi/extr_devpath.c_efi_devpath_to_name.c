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
struct TYPE_2__ {int /*<<< orphan*/  (* AllocatePool ) (int /*<<< orphan*/ ,size_t,void**) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;
typedef  char CHAR16 ;

/* Variables and functions */
 TYPE_1__* BS ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EfiLoaderData ; 
 char* efi_translate_devpath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t,void**) ; 
 int utf8_to_ucs2 (char*,char**,size_t*) ; 

__attribute__((used)) static CHAR16 *
efi_devpath_to_name(EFI_DEVICE_PATH *devpath)
{
	char *name = NULL;
	CHAR16 *ptr = NULL;
	size_t len;
	int rv;

	name = efi_translate_devpath(devpath);
	if (name == NULL)
		return (NULL);

	/*
	 * We need to return memory from AllocatePool, so it can be freed
	 * with FreePool() in efi_free_devpath_name().
	 */
	rv = utf8_to_ucs2(name, &ptr, &len);
	free(name);
	if (rv == 0) {
		CHAR16 *out = NULL;
		EFI_STATUS status;

		status = BS->AllocatePool(EfiLoaderData, len, (void **)&out);
		if (EFI_ERROR(status)) {
			free(ptr);
                	return (out);
		}
		memcpy(out, ptr, len);
		free(ptr);
		ptr = out;
	}
	
	return (ptr);
}