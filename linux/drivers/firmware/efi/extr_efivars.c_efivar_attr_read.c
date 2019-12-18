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
struct efi_variable {int DataSize; int Attributes; int /*<<< orphan*/  Data; } ;
struct efivar_entry {struct efi_variable var; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EFI_VARIABLE_APPEND_WRITE ; 
 int EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS ; 
 int EFI_VARIABLE_BOOTSERVICE_ACCESS ; 
 int EFI_VARIABLE_HARDWARE_ERROR_RECORD ; 
 int EFI_VARIABLE_NON_VOLATILE ; 
 int EFI_VARIABLE_RUNTIME_ACCESS ; 
 int EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ efivar_entry_get (struct efivar_entry*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t
efivar_attr_read(struct efivar_entry *entry, char *buf)
{
	struct efi_variable *var = &entry->var;
	char *str = buf;

	if (!entry || !buf)
		return -EINVAL;

	var->DataSize = 1024;
	if (efivar_entry_get(entry, &var->Attributes, &var->DataSize, var->Data))
		return -EIO;

	if (var->Attributes & EFI_VARIABLE_NON_VOLATILE)
		str += sprintf(str, "EFI_VARIABLE_NON_VOLATILE\n");
	if (var->Attributes & EFI_VARIABLE_BOOTSERVICE_ACCESS)
		str += sprintf(str, "EFI_VARIABLE_BOOTSERVICE_ACCESS\n");
	if (var->Attributes & EFI_VARIABLE_RUNTIME_ACCESS)
		str += sprintf(str, "EFI_VARIABLE_RUNTIME_ACCESS\n");
	if (var->Attributes & EFI_VARIABLE_HARDWARE_ERROR_RECORD)
		str += sprintf(str, "EFI_VARIABLE_HARDWARE_ERROR_RECORD\n");
	if (var->Attributes & EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS)
		str += sprintf(str,
			"EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS\n");
	if (var->Attributes &
			EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
		str += sprintf(str,
			"EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS\n");
	if (var->Attributes & EFI_VARIABLE_APPEND_WRITE)
		str += sprintf(str, "EFI_VARIABLE_APPEND_WRITE\n");
	return str - buf;
}