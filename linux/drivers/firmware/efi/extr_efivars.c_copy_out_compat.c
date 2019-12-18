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
struct efi_variable {int /*<<< orphan*/  Attributes; int /*<<< orphan*/  DataSize; int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/  Data; int /*<<< orphan*/  VariableName; } ;
struct compat_efi_variable {int /*<<< orphan*/  Attributes; int /*<<< orphan*/  DataSize; int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/  Data; int /*<<< orphan*/  VariableName; } ;

/* Variables and functions */
 int EFI_VAR_NAME_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
copy_out_compat(struct efi_variable *dst, struct compat_efi_variable *src)
{
	memcpy(dst->VariableName, src->VariableName, EFI_VAR_NAME_LEN);
	memcpy(dst->Data, src->Data, sizeof(src->Data));

	dst->VendorGuid = src->VendorGuid;
	dst->DataSize = src->DataSize;
	dst->Attributes = src->Attributes;
}