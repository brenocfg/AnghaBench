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
struct TYPE_2__ {scalar_t__ Data; int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/ * VariableName; } ;
struct efivar_entry {TYPE_1__ var; } ;
typedef  int /*<<< orphan*/  guid ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */
 int EFI_VARIABLE_BOOTSERVICE_ACCESS ; 
 int EFI_VARIABLE_NON_VOLATILE ; 
 int EFI_VARIABLE_RUNTIME_ACCESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LINUX_EFI_LOADER_ENTRY_GUID ; 
 int /*<<< orphan*/  efibc_str_to_str16 (char const*,int /*<<< orphan*/ *) ; 
 int efivar_entry_set_safe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,size_t,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct efivar_entry*) ; 
 struct efivar_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int efibc_set_variable(const char *name, const char *value)
{
	int ret;
	efi_guid_t guid = LINUX_EFI_LOADER_ENTRY_GUID;
	struct efivar_entry *entry;
	size_t size = (strlen(value) + 1) * sizeof(efi_char16_t);

	if (size > sizeof(entry->var.Data)) {
		pr_err("value is too large (%zu bytes) for '%s' EFI variable\n", size, name);
		return -EINVAL;
	}

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		pr_err("failed to allocate efivar entry for '%s' EFI variable\n", name);
		return -ENOMEM;
	}

	efibc_str_to_str16(name, entry->var.VariableName);
	efibc_str_to_str16(value, (efi_char16_t *)entry->var.Data);
	memcpy(&entry->var.VendorGuid, &guid, sizeof(guid));

	ret = efivar_entry_set_safe(entry->var.VariableName,
				    entry->var.VendorGuid,
				    EFI_VARIABLE_NON_VOLATILE
				    | EFI_VARIABLE_BOOTSERVICE_ACCESS
				    | EFI_VARIABLE_RUNTIME_ACCESS,
				    false, size, entry->var.Data);

	if (ret)
		pr_err("failed to set %s EFI variable: 0x%x\n",
		       name, ret);

	kfree(entry);
	return ret;
}