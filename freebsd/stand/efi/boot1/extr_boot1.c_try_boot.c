#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  devhandle; int /*<<< orphan*/  devpath; } ;
typedef  TYPE_1__ dev_info_t ;
struct TYPE_10__ {scalar_t__ (* load ) (int /*<<< orphan*/ ,TYPE_1__*,void**,size_t*) ;char* name; } ;
typedef  TYPE_2__ boot_module_t ;
struct TYPE_12__ {scalar_t__ (* LoadImage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *) ;scalar_t__ (* StartImage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {size_t LoadOptionsSize; char* LoadOptions; int /*<<< orphan*/  DeviceHandle; } ;
typedef  scalar_t__ EFI_STATUS ;
typedef  TYPE_3__ EFI_LOADED_IMAGE ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;

/* Variables and functions */
 TYPE_8__* BS ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DSTALL (int) ; 
 int /*<<< orphan*/  EFI_ERROR_CODE (scalar_t__) ; 
 scalar_t__ EFI_NOT_FOUND ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  IH ; 
 int /*<<< orphan*/  LoadedImageGUID ; 
 scalar_t__ OpenProtocolByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  PATH_CONFIG ; 
 int /*<<< orphan*/  PATH_DOTCONFIG ; 
 int /*<<< orphan*/  PATH_LOADER_EFI ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  efi_devpath_last_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*,void**,size_t*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_1__*,void**,size_t*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

EFI_STATUS
try_boot(const boot_module_t *mod, dev_info_t *dev, void *loaderbuf, size_t loadersize)
{
	size_t bufsize, cmdsize;
	void *buf;
	char *cmd;
	EFI_HANDLE loaderhandle;
	EFI_LOADED_IMAGE *loaded_image;
	EFI_STATUS status;

	/*
	 * Read in and parse the command line from /boot.config or /boot/config,
	 * if present. We'll pass it the next stage via a simple ASCII
	 * string. loader.efi has a hack for ASCII strings, so we'll use that to
	 * keep the size down here. We only try to read the alternate file if
	 * we get EFI_NOT_FOUND because all other errors mean that the boot_module
	 * had troubles with the filesystem. We could return early, but we'll let
	 * loading the actual kernel sort all that out. Since these files are
	 * optional, we don't report errors in trying to read them.
	 */
	cmd = NULL;
	cmdsize = 0;
	status = mod->load(PATH_DOTCONFIG, dev, &buf, &bufsize);
	if (status == EFI_NOT_FOUND)
		status = mod->load(PATH_CONFIG, dev, &buf, &bufsize);
	if (status == EFI_SUCCESS) {
		cmdsize = bufsize + 1;
		cmd = malloc(cmdsize);
		if (cmd == NULL)
			goto errout;
		memcpy(cmd, buf, bufsize);
		cmd[bufsize] = '\0';
		free(buf);
		buf = NULL;
	}

	if ((status = BS->LoadImage(TRUE, IH, efi_devpath_last_node(dev->devpath),
	    loaderbuf, loadersize, &loaderhandle)) != EFI_SUCCESS) {
		printf("Failed to load image provided by %s, size: %zu, (%lu)\n",
		     mod->name, loadersize, EFI_ERROR_CODE(status));
		goto errout;
	}

	status = OpenProtocolByHandle(loaderhandle, &LoadedImageGUID,
	    (void **)&loaded_image);
	if (status != EFI_SUCCESS) {
		printf("Failed to query LoadedImage provided by %s (%lu)\n",
		    mod->name, EFI_ERROR_CODE(status));
		goto errout;
	}

	if (cmd != NULL)
		printf("    command args: %s\n", cmd);

	loaded_image->DeviceHandle = dev->devhandle;
	loaded_image->LoadOptionsSize = cmdsize;
	loaded_image->LoadOptions = cmd;

	DPRINTF("Starting '%s' in 5 seconds...", PATH_LOADER_EFI);
	DSTALL(1000000);
	DPRINTF(".");
	DSTALL(1000000);
	DPRINTF(".");
	DSTALL(1000000);
	DPRINTF(".");
	DSTALL(1000000);
	DPRINTF(".");
	DSTALL(1000000);
	DPRINTF(".\n");

	if ((status = BS->StartImage(loaderhandle, NULL, NULL)) !=
	    EFI_SUCCESS) {
		printf("Failed to start image provided by %s (%lu)\n",
		    mod->name, EFI_ERROR_CODE(status));
		loaded_image->LoadOptionsSize = 0;
		loaded_image->LoadOptions = NULL;
	}

errout:
	if (cmd != NULL)
		free(cmd);
	if (buf != NULL)
		free(buf);
	if (loaderbuf != NULL)
		free(loaderbuf);

	return (status);
}