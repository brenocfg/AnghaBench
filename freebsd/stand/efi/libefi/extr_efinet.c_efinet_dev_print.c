#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* dv_name; } ;
typedef  int /*<<< orphan*/ * EFI_HANDLE ;
typedef  char CHAR16 ;

/* Variables and functions */
 char* efi_devpath_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * efi_find_handle (TYPE_1__*,int) ; 
 int /*<<< orphan*/  efi_free_devpath_name (char*) ; 
 int /*<<< orphan*/  efi_lookup_devpath (int /*<<< orphan*/ *) ; 
 TYPE_1__ efinet_dev ; 
 int pager_output (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static int
efinet_dev_print(int verbose)
{
	CHAR16 *text;
	EFI_HANDLE h;
	int unit, ret = 0;

	printf("%s devices:", efinet_dev.dv_name);
	if ((ret = pager_output("\n")) != 0)
		return (ret);

	for (unit = 0, h = efi_find_handle(&efinet_dev, 0);
	    h != NULL; h = efi_find_handle(&efinet_dev, ++unit)) {
		printf("    %s%d:", efinet_dev.dv_name, unit);
		if (verbose) {
			text = efi_devpath_name(efi_lookup_devpath(h));
			if (text != NULL) {
				printf("    %S", text);
				efi_free_devpath_name(text);
			}
		}
		if ((ret = pager_output("\n")) != 0)
			break;
	}
	return (ret);
}