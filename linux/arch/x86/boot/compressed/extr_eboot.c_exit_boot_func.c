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
struct exit_boot_struct {TYPE_1__* efi; } ;
struct efi_boot_memmap {scalar_t__* map; int /*<<< orphan*/ * map_size; int /*<<< orphan*/ * desc_ver; int /*<<< orphan*/ * desc_size; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  int /*<<< orphan*/  efi_status_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {unsigned long efi_systab; unsigned long efi_memmap; unsigned long efi_systab_hi; unsigned long efi_memmap_hi; int /*<<< orphan*/  efi_memmap_size; int /*<<< orphan*/  efi_memdesc_version; int /*<<< orphan*/  efi_memdesc_size; int /*<<< orphan*/  efi_loader_signature; } ;

/* Variables and functions */
 char* EFI32_LOADER_SIGNATURE ; 
 char* EFI64_LOADER_SIGNATURE ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 scalar_t__ efi_is_64bit () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static efi_status_t exit_boot_func(efi_system_table_t *sys_table_arg,
				   struct efi_boot_memmap *map,
				   void *priv)
{
	const char *signature;
	struct exit_boot_struct *p = priv;

	signature = efi_is_64bit() ? EFI64_LOADER_SIGNATURE
				   : EFI32_LOADER_SIGNATURE;
	memcpy(&p->efi->efi_loader_signature, signature, sizeof(__u32));

	p->efi->efi_systab		= (unsigned long)sys_table_arg;
	p->efi->efi_memdesc_size	= *map->desc_size;
	p->efi->efi_memdesc_version	= *map->desc_ver;
	p->efi->efi_memmap		= (unsigned long)*map->map;
	p->efi->efi_memmap_size		= *map->map_size;

#ifdef CONFIG_X86_64
	p->efi->efi_systab_hi		= (unsigned long)sys_table_arg >> 32;
	p->efi->efi_memmap_hi		= (unsigned long)*map->map >> 32;
#endif

	return EFI_SUCCESS;
}