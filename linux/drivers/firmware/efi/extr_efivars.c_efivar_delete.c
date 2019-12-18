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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct efivar_entry {int /*<<< orphan*/  scanning; } ;
struct efi_variable {int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/ * VariableName; } ;
struct compat_efi_variable {int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/ * VariableName; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ __efivar_entry_delete (struct efivar_entry*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct efivar_entry* efivar_entry_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ efivar_entry_iter_begin () ; 
 int /*<<< orphan*/  efivar_entry_iter_end () ; 
 int /*<<< orphan*/  efivar_sysfs_list ; 
 int /*<<< orphan*/  efivar_unregister (struct efivar_entry*) ; 
 scalar_t__ in_compat_syscall () ; 

__attribute__((used)) static ssize_t efivar_delete(struct file *filp, struct kobject *kobj,
			     struct bin_attribute *bin_attr,
			     char *buf, loff_t pos, size_t count)
{
	struct efi_variable *del_var = (struct efi_variable *)buf;
	struct compat_efi_variable *compat;
	struct efivar_entry *entry;
	efi_char16_t *name;
	efi_guid_t vendor;
	int err = 0;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (in_compat_syscall()) {
		if (count != sizeof(*compat))
			return -EINVAL;

		compat = (struct compat_efi_variable *)buf;
		name = compat->VariableName;
		vendor = compat->VendorGuid;
	} else {
		if (count != sizeof(*del_var))
			return -EINVAL;

		name = del_var->VariableName;
		vendor = del_var->VendorGuid;
	}

	if (efivar_entry_iter_begin())
		return -EINTR;
	entry = efivar_entry_find(name, vendor, &efivar_sysfs_list, true);
	if (!entry)
		err = -EINVAL;
	else if (__efivar_entry_delete(entry))
		err = -EIO;

	if (err) {
		efivar_entry_iter_end();
		return err;
	}

	if (!entry->scanning) {
		efivar_entry_iter_end();
		efivar_unregister(entry);
	} else
		efivar_entry_iter_end();

	/* It's dead Jim.... */
	return count;
}