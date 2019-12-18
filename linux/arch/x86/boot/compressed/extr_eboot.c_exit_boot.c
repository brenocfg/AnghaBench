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
struct setup_data {int dummy; } ;
struct exit_boot_struct {int /*<<< orphan*/ * efi; struct boot_params* boot_params; } ;
struct efi_boot_memmap {unsigned long* map_size; unsigned long* desc_size; unsigned long* key_ptr; unsigned long* buff_size; int /*<<< orphan*/ * desc_ver; int /*<<< orphan*/ ** map; } ;
struct boot_params {int alt_mem_k; int /*<<< orphan*/  efi_info; } ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_memory_desc_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ allocate_e820 (struct boot_params*,struct setup_data**,int /*<<< orphan*/ *) ; 
 scalar_t__ efi_exit_boot_services (int /*<<< orphan*/ ,void*,struct efi_boot_memmap*,struct exit_boot_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_boot_func ; 
 scalar_t__ setup_e820 (struct boot_params*,struct setup_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_table ; 

__attribute__((used)) static efi_status_t exit_boot(struct boot_params *boot_params, void *handle)
{
	unsigned long map_sz, key, desc_size, buff_size;
	efi_memory_desc_t *mem_map;
	struct setup_data *e820ext = NULL;
	__u32 e820ext_size = 0;
	efi_status_t status;
	__u32 desc_version;
	struct efi_boot_memmap map;
	struct exit_boot_struct priv;

	map.map			= &mem_map;
	map.map_size		= &map_sz;
	map.desc_size		= &desc_size;
	map.desc_ver		= &desc_version;
	map.key_ptr		= &key;
	map.buff_size		= &buff_size;
	priv.boot_params	= boot_params;
	priv.efi		= &boot_params->efi_info;

	status = allocate_e820(boot_params, &e820ext, &e820ext_size);
	if (status != EFI_SUCCESS)
		return status;

	/* Might as well exit boot services now */
	status = efi_exit_boot_services(sys_table, handle, &map, &priv,
					exit_boot_func);
	if (status != EFI_SUCCESS)
		return status;

	/* Historic? */
	boot_params->alt_mem_k	= 32 * 1024;

	status = setup_e820(boot_params, e820ext, e820ext_size);
	if (status != EFI_SUCCESS)
		return status;

	return EFI_SUCCESS;
}