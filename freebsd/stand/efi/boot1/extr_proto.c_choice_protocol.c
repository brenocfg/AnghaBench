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
typedef  int /*<<< orphan*/  dev_info_t ;
typedef  int /*<<< orphan*/  boot_order ;
typedef  int /*<<< orphan*/  boot_module_t ;
typedef  int /*<<< orphan*/  boot_current ;
typedef  unsigned int UINTN ;
typedef  int UINT16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* Exit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* status ) () ;} ;
typedef  scalar_t__ EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 TYPE_2__* BS ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  EFI_OUT_OF_RESOURCES ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  IH ; 
 char* PATH_LOADER_EFI ; 
 TYPE_1__** boot_modules ; 
 scalar_t__ efi_global_getenv (char*,...) ; 
 scalar_t__ load_loader (int /*<<< orphan*/  const**,int /*<<< orphan*/ **,void**,size_t*,int) ; 
 unsigned int num_boot_modules ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** prio_str ; 
 int probe_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  try_boot (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void*,size_t) ; 

void
choice_protocol(EFI_HANDLE *handles, UINTN nhandles, EFI_DEVICE_PATH *imgpath)
{
	UINT16 boot_current;
	size_t sz;
	UINT16 boot_order[100];
	unsigned i;
	int rv;
	EFI_STATUS status;
	const boot_module_t *mod;
	dev_info_t *dev;
	void *loaderbuf;
	size_t loadersize;

	/* Report UEFI Boot Manager Protocol details */
	boot_current = 0;
	sz = sizeof(boot_current);
	if (efi_global_getenv("BootCurrent", &boot_current, &sz) == EFI_SUCCESS) {
		printf("   BootCurrent: %04x\n", boot_current);

		sz = sizeof(boot_order);
		if (efi_global_getenv("BootOrder", &boot_order, &sz) == EFI_SUCCESS) {
			printf("   BootOrder:");
			for (i = 0; i < sz / sizeof(boot_order[0]); i++)
				printf(" %04x%s", boot_order[i],
				    boot_order[i] == boot_current ? "[*]" : "");
			printf("\n");
		}
	}

#ifdef TEST_FAILURE
	/*
	 * For testing failover scenarios, it's nice to be able to fail fast.
	 * Define TEST_FAILURE to create a boot1.efi that always fails after
	 * reporting the boot manager protocol details.
	 */
	BS->Exit(IH, EFI_OUT_OF_RESOURCES, 0, NULL);
#endif

	/* Scan all partitions, probing with all modules. */
	printf("   Probing %zu block devices...", nhandles);
	DPRINTF("\n");
	for (i = 0; i < nhandles; i++) {
		rv = probe_handle(handles[i], imgpath);
#ifdef EFI_DEBUG
		printf("%c", "x.+*"[rv + 1]);
#else
		printf("%s\n", prio_str[rv + 1]);
#endif
	}
	printf(" done\n");


	/* Status summary. */
	for (i = 0; i < num_boot_modules; i++) {
		printf("    ");
		boot_modules[i]->status();
	}

	status = load_loader(&mod, &dev, &loaderbuf, &loadersize, 1);
	if (status != EFI_SUCCESS) {
		status = load_loader(&mod, &dev, &loaderbuf, &loadersize, 0);
		if (status != EFI_SUCCESS) {
			printf("Failed to load '%s'\n", PATH_LOADER_EFI);
			return;
		}
	}

	try_boot(mod, dev, loaderbuf, loadersize);
}