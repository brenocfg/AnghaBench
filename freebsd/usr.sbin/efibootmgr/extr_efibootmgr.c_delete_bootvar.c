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

/* Variables and functions */
 int /*<<< orphan*/  EFI_GLOBAL_GUID ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,int) ; 
 scalar_t__ efi_del_variable (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  remove_from_order (int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
delete_bootvar(int bootnum)
{
	char *name;
	int defer = 0;

	/*
	 * Try to delete the boot variable and remocve it
	 * from the boot order. We always do both actions
	 * to make it easy to clean up from oopses.
	 */
	if (bootnum < 0 || bootnum > 0xffff)
		errx(1, "Bad boot variable %#x", bootnum);
	asprintf(&name, "%s%04X", "Boot", bootnum);
	if (name == NULL)
		err(1, "asprintf");
	printf("Removing boot variable '%s'\n", name);
	if (efi_del_variable(EFI_GLOBAL_GUID, name) < 0) {
		defer = 1;
		warn("cannot delete variable %s", name);
	}
	printf("Removing 0x%x from BootOrder\n", bootnum);
	remove_from_order(bootnum);
	free(name);
	if (defer)
		exit(defer);
}