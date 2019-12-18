#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kset; } ;
struct TYPE_4__ {int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/ * VariableName; } ;
struct efivar_entry {TYPE_2__ kobj; TYPE_1__ var; } ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */
 unsigned long EFI_VARIABLE_GUID_LEN ; 
 int EINTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  efi_guid_to_str (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ efivar_entry_add (struct efivar_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivar_ktype ; 
 int /*<<< orphan*/  efivar_sysfs_list ; 
 int /*<<< orphan*/  efivar_unregister (struct efivar_entry*) ; 
 int /*<<< orphan*/  efivars_kset ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int kobject_init_and_add (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  kobject_uevent (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucs2_as_utf8 (char*,int /*<<< orphan*/ *,int) ; 
 unsigned long ucs2_utf8size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
efivar_create_sysfs_entry(struct efivar_entry *new_var)
{
	int short_name_size;
	char *short_name;
	unsigned long utf8_name_size;
	efi_char16_t *variable_name = new_var->var.VariableName;
	int ret;

	/*
	 * Length of the variable bytes in UTF8, plus the '-' separator,
	 * plus the GUID, plus trailing NUL
	 */
	utf8_name_size = ucs2_utf8size(variable_name);
	short_name_size = utf8_name_size + 1 + EFI_VARIABLE_GUID_LEN + 1;

	short_name = kmalloc(short_name_size, GFP_KERNEL);
	if (!short_name)
		return -ENOMEM;

	ucs2_as_utf8(short_name, variable_name, short_name_size);

	/* This is ugly, but necessary to separate one vendor's
	   private variables from another's.         */
	short_name[utf8_name_size] = '-';
	efi_guid_to_str(&new_var->var.VendorGuid,
			 short_name + utf8_name_size + 1);

	new_var->kobj.kset = efivars_kset;

	ret = kobject_init_and_add(&new_var->kobj, &efivar_ktype,
				   NULL, "%s", short_name);
	kfree(short_name);
	if (ret)
		return ret;

	kobject_uevent(&new_var->kobj, KOBJ_ADD);
	if (efivar_entry_add(new_var, &efivar_sysfs_list)) {
		efivar_unregister(new_var);
		return -EINTR;
	}

	return 0;
}