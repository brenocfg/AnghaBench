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
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int efi_get_next_variable_name (int /*<<< orphan*/ **,char**) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  print_var (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
print_variables(void)
{
	int rv;
	char *name = NULL;
	efi_guid_t *guid = NULL;

	while ((rv = efi_get_next_variable_name(&guid, &name)) > 0)
		print_var(guid, name);

	if (rv < 0)
		err(1, "Error listing names");
}