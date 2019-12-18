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
struct linux_efi_memreserve {int /*<<< orphan*/  count; scalar_t__ size; scalar_t__ next; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  LINUX_EFI_MEMRESERVE_TABLE_GUID ; 
 int /*<<< orphan*/  allocate_pool ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  install_configuration_table ; 
 int /*<<< orphan*/  pr_efi_err (int /*<<< orphan*/ *,char*) ; 

void install_memreserve_table(efi_system_table_t *sys_table_arg)
{
	struct linux_efi_memreserve *rsv;
	efi_guid_t memreserve_table_guid = LINUX_EFI_MEMRESERVE_TABLE_GUID;
	efi_status_t status;

	status = efi_call_early(allocate_pool, EFI_LOADER_DATA, sizeof(*rsv),
				(void **)&rsv);
	if (status != EFI_SUCCESS) {
		pr_efi_err(sys_table_arg, "Failed to allocate memreserve entry!\n");
		return;
	}

	rsv->next = 0;
	rsv->size = 0;
	atomic_set(&rsv->count, 0);

	status = efi_call_early(install_configuration_table,
				&memreserve_table_guid,
				rsv);
	if (status != EFI_SUCCESS)
		pr_efi_err(sys_table_arg, "Failed to install memreserve config table!\n");
}