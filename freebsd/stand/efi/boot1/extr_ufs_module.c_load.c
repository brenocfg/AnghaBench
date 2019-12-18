#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ufs_ino_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  devpath; } ;
typedef  TYPE_1__ dev_info_t ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  EFI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EFI_NOT_FOUND ; 
 int /*<<< orphan*/  EFI_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 
 int /*<<< orphan*/ * efi_devpath_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efi_free_devpath_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fsread (int,void*,size_t) ; 
 scalar_t__ fsread_size (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ init_dev (TYPE_1__*) ; 
 int lookup (char const*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static EFI_STATUS
load(const char *filepath, dev_info_t *dev, void **bufp, size_t *bufsize)
{
	ufs_ino_t ino;
	size_t size;
	ssize_t read;
	void *buf;

#ifdef EFI_DEBUG
	{
		CHAR16 *text = efi_devpath_name(dev->devpath);
		DPRINTF("UFS Loading '%s' from %S\n", filepath, text);
		efi_free_devpath_name(text);
	}
#endif
	if (init_dev(dev) < 0) {
		DPRINTF("Failed to init device\n");
		return (EFI_UNSUPPORTED);
	}

	if ((ino = lookup(filepath)) == 0) {
		DPRINTF("Failed to lookup '%s' (file not found?)\n", filepath);
		return (EFI_NOT_FOUND);
	}

	if (fsread_size(ino, NULL, 0, &size) < 0 || size <= 0) {
		printf("Failed to read size of '%s' ino: %d\n", filepath, ino);
		return (EFI_INVALID_PARAMETER);
	}

	buf = malloc(size);
	if (buf == NULL) {
		printf("Failed to allocate read buffer %zu for '%s'\n",
		    size, filepath);
		return (EFI_OUT_OF_RESOURCES);
	}

	read = fsread(ino, buf, size);
	if ((size_t)read != size) {
		printf("Failed to read '%s' (%zd != %zu)\n", filepath, read,
		    size);
		free(buf);
		return (EFI_INVALID_PARAMETER);
	}

	DPRINTF("Load complete\n");

	*bufp = buf;
	*bufsize = size;

	return (EFI_SUCCESS);
}