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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  fdt_val64 ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RANDOMIZE_BASE ; 
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 scalar_t__ EFI_LOAD_ERROR ; 
 scalar_t__ EFI_NOT_FOUND ; 
 scalar_t__ EFI_SUCCESS ; 
 int FDT_ERR_NOSPACE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ U32_MAX ; 
 scalar_t__ U64_MAX ; 
 scalar_t__ cpu_to_fdt64 (scalar_t__) ; 
 scalar_t__ efi_get_random_bytes (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int fdt_add_subnode (void*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fdt_check_header (void*) ; 
 int fdt_create_empty_tree (void*,int) ; 
 int /*<<< orphan*/  fdt_del_mem_rsv (void*,int) ; 
 int fdt_num_mem_rsv (void*) ; 
 int fdt_open_into (void*,void*,int) ; 
 int /*<<< orphan*/  fdt_pack (void*) ; 
 int fdt_setprop (void*,int,char*,char*,scalar_t__) ; 
 int fdt_setprop_var (void*,int,char*,scalar_t__) ; 
 int fdt_subnode_offset (void*,int /*<<< orphan*/ ,char*) ; 
 unsigned long fdt_totalsize (void*) ; 
 int /*<<< orphan*/  fdt_update_cell_size (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pr_efi_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static efi_status_t update_fdt(efi_system_table_t *sys_table, void *orig_fdt,
			       unsigned long orig_fdt_size,
			       void *fdt, int new_fdt_size, char *cmdline_ptr,
			       u64 initrd_addr, u64 initrd_size)
{
	int node, num_rsv;
	int status;
	u32 fdt_val32;
	u64 fdt_val64;

	/* Do some checks on provided FDT, if it exists: */
	if (orig_fdt) {
		if (fdt_check_header(orig_fdt)) {
			pr_efi_err(sys_table, "Device Tree header not valid!\n");
			return EFI_LOAD_ERROR;
		}
		/*
		 * We don't get the size of the FDT if we get if from a
		 * configuration table:
		 */
		if (orig_fdt_size && fdt_totalsize(orig_fdt) > orig_fdt_size) {
			pr_efi_err(sys_table, "Truncated device tree! foo!\n");
			return EFI_LOAD_ERROR;
		}
	}

	if (orig_fdt) {
		status = fdt_open_into(orig_fdt, fdt, new_fdt_size);
	} else {
		status = fdt_create_empty_tree(fdt, new_fdt_size);
		if (status == 0) {
			/*
			 * Any failure from the following function is
			 * non-critical:
			 */
			fdt_update_cell_size(sys_table, fdt);
		}
	}

	if (status != 0)
		goto fdt_set_fail;

	/*
	 * Delete all memory reserve map entries. When booting via UEFI,
	 * kernel will use the UEFI memory map to find reserved regions.
	 */
	num_rsv = fdt_num_mem_rsv(fdt);
	while (num_rsv-- > 0)
		fdt_del_mem_rsv(fdt, num_rsv);

	node = fdt_subnode_offset(fdt, 0, "chosen");
	if (node < 0) {
		node = fdt_add_subnode(fdt, 0, "chosen");
		if (node < 0) {
			/* 'node' is an error code when negative: */
			status = node;
			goto fdt_set_fail;
		}
	}

	if (cmdline_ptr != NULL && strlen(cmdline_ptr) > 0) {
		status = fdt_setprop(fdt, node, "bootargs", cmdline_ptr,
				     strlen(cmdline_ptr) + 1);
		if (status)
			goto fdt_set_fail;
	}

	/* Set initrd address/end in device tree, if present */
	if (initrd_size != 0) {
		u64 initrd_image_end;
		u64 initrd_image_start = cpu_to_fdt64(initrd_addr);

		status = fdt_setprop_var(fdt, node, "linux,initrd-start", initrd_image_start);
		if (status)
			goto fdt_set_fail;

		initrd_image_end = cpu_to_fdt64(initrd_addr + initrd_size);
		status = fdt_setprop_var(fdt, node, "linux,initrd-end", initrd_image_end);
		if (status)
			goto fdt_set_fail;
	}

	/* Add FDT entries for EFI runtime services in chosen node. */
	node = fdt_subnode_offset(fdt, 0, "chosen");
	fdt_val64 = cpu_to_fdt64((u64)(unsigned long)sys_table);

	status = fdt_setprop_var(fdt, node, "linux,uefi-system-table", fdt_val64);
	if (status)
		goto fdt_set_fail;

	fdt_val64 = U64_MAX; /* placeholder */

	status = fdt_setprop_var(fdt, node, "linux,uefi-mmap-start", fdt_val64);
	if (status)
		goto fdt_set_fail;

	fdt_val32 = U32_MAX; /* placeholder */

	status = fdt_setprop_var(fdt, node, "linux,uefi-mmap-size", fdt_val32);
	if (status)
		goto fdt_set_fail;

	status = fdt_setprop_var(fdt, node, "linux,uefi-mmap-desc-size", fdt_val32);
	if (status)
		goto fdt_set_fail;

	status = fdt_setprop_var(fdt, node, "linux,uefi-mmap-desc-ver", fdt_val32);
	if (status)
		goto fdt_set_fail;

	if (IS_ENABLED(CONFIG_RANDOMIZE_BASE)) {
		efi_status_t efi_status;

		efi_status = efi_get_random_bytes(sys_table, sizeof(fdt_val64),
						  (u8 *)&fdt_val64);
		if (efi_status == EFI_SUCCESS) {
			status = fdt_setprop_var(fdt, node, "kaslr-seed", fdt_val64);
			if (status)
				goto fdt_set_fail;
		} else if (efi_status != EFI_NOT_FOUND) {
			return efi_status;
		}
	}

	/* Shrink the FDT back to its minimum size: */
	fdt_pack(fdt);

	return EFI_SUCCESS;

fdt_set_fail:
	if (status == -FDT_ERR_NOSPACE)
		return EFI_BUFFER_TOO_SMALL;

	return EFI_LOAD_ERROR;
}