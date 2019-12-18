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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_GLOBAL_GUID ; 
 int /*<<< orphan*/  LOAD_OPTION_ACTIVE ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,int) ; 
 scalar_t__ efi_get_variable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  le32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ set_bootvar (char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
handle_activity(int bootnum, bool active)
{
	uint32_t attrs, load_attrs;
	uint8_t *data;
	size_t size;
	char *name;

	asprintf(&name, "%s%04X", "Boot", bootnum);
	if (name == NULL)
		err(1, "asprintf");
	if (efi_get_variable(EFI_GLOBAL_GUID, name, &data, &size, &attrs) < 0)
		err(1, "No such bootvar %s\n", name);

	load_attrs = le32dec(data);

	if (active)
		load_attrs |= LOAD_OPTION_ACTIVE;
	else
		load_attrs &= ~LOAD_OPTION_ACTIVE;

	le32enc(data, load_attrs);

	if (set_bootvar(name, data, size) < 0)
		err(1, "handle activity efi_set_variable");
}