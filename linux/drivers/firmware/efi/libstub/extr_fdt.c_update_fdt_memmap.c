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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct efi_boot_memmap {int /*<<< orphan*/ * desc_ver; int /*<<< orphan*/ * desc_size; int /*<<< orphan*/ * map_size; scalar_t__* map; } ;
typedef  int /*<<< orphan*/  efi_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_LOAD_ERROR ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_fdt64 (unsigned long) ; 
 int fdt_path_offset (void*,char*) ; 
 int fdt_setprop_inplace_var (void*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static efi_status_t update_fdt_memmap(void *fdt, struct efi_boot_memmap *map)
{
	int node = fdt_path_offset(fdt, "/chosen");
	u64 fdt_val64;
	u32 fdt_val32;
	int err;

	if (node < 0)
		return EFI_LOAD_ERROR;

	fdt_val64 = cpu_to_fdt64((unsigned long)*map->map);

	err = fdt_setprop_inplace_var(fdt, node, "linux,uefi-mmap-start", fdt_val64);
	if (err)
		return EFI_LOAD_ERROR;

	fdt_val32 = cpu_to_fdt32(*map->map_size);

	err = fdt_setprop_inplace_var(fdt, node, "linux,uefi-mmap-size", fdt_val32);
	if (err)
		return EFI_LOAD_ERROR;

	fdt_val32 = cpu_to_fdt32(*map->desc_size);

	err = fdt_setprop_inplace_var(fdt, node, "linux,uefi-mmap-desc-size", fdt_val32);
	if (err)
		return EFI_LOAD_ERROR;

	fdt_val32 = cpu_to_fdt32(*map->desc_ver);

	err = fdt_setprop_inplace_var(fdt, node, "linux,uefi-mmap-desc-ver", fdt_val32);
	if (err)
		return EFI_LOAD_ERROR;

	return EFI_SUCCESS;
}