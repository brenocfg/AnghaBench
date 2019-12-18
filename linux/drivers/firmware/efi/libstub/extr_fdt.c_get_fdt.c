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
typedef  int /*<<< orphan*/  efi_system_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_TREE_GUID ; 
 scalar_t__ fdt_check_header (void*) ; 
 unsigned long fdt_totalsize (void*) ; 
 void* get_efi_config_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_efi_err (int /*<<< orphan*/ *,char*) ; 

void *get_fdt(efi_system_table_t *sys_table, unsigned long *fdt_size)
{
	void *fdt;

	fdt = get_efi_config_table(sys_table, DEVICE_TREE_GUID);

	if (!fdt)
		return NULL;

	if (fdt_check_header(fdt) != 0) {
		pr_efi_err(sys_table, "Invalid header detected on UEFI supplied FDT, ignoring ...\n");
		return NULL;
	}
	*fdt_size = fdt_totalsize(fdt);
	return fdt;
}