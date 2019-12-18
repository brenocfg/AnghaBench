#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct efi_info {int efi_systab; scalar_t__ efi_memmap_hi; scalar_t__ efi_systab_hi; int /*<<< orphan*/  efi_loader_signature; } ;
struct TYPE_4__ {unsigned long tables; unsigned int nr_tables; } ;
typedef  TYPE_1__ efi_system_table_64_t ;
struct TYPE_5__ {unsigned long tables; unsigned int nr_tables; } ;
typedef  TYPE_2__ efi_system_table_32_t ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
typedef  int __u64 ;
struct TYPE_6__ {struct efi_info efi_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI32_LOADER_SIGNATURE ; 
 int /*<<< orphan*/  EFI64_LOADER_SIGNATURE ; 
 int /*<<< orphan*/  __efi_get_rsdp_addr (unsigned long,unsigned int,int) ; 
 TYPE_3__* boot_params ; 
 int /*<<< orphan*/  debug_putstr (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static acpi_physical_address efi_get_rsdp_addr(void)
{
#ifdef CONFIG_EFI
	unsigned long systab, config_tables;
	unsigned int nr_tables;
	struct efi_info *ei;
	bool efi_64;
	char *sig;

	ei = &boot_params->efi_info;
	sig = (char *)&ei->efi_loader_signature;

	if (!strncmp(sig, EFI64_LOADER_SIGNATURE, 4)) {
		efi_64 = true;
	} else if (!strncmp(sig, EFI32_LOADER_SIGNATURE, 4)) {
		efi_64 = false;
	} else {
		debug_putstr("Wrong EFI loader signature.\n");
		return 0;
	}

	/* Get systab from boot params. */
#ifdef CONFIG_X86_64
	systab = ei->efi_systab | ((__u64)ei->efi_systab_hi << 32);
#else
	if (ei->efi_systab_hi || ei->efi_memmap_hi) {
		debug_putstr("Error getting RSDP address: EFI system table located above 4GB.\n");
		return 0;
	}
	systab = ei->efi_systab;
#endif
	if (!systab)
		error("EFI system table not found.");

	/* Handle EFI bitness properly */
	if (efi_64) {
		efi_system_table_64_t *stbl = (efi_system_table_64_t *)systab;

		config_tables	= stbl->tables;
		nr_tables	= stbl->nr_tables;
	} else {
		efi_system_table_32_t *stbl = (efi_system_table_32_t *)systab;

		config_tables	= stbl->tables;
		nr_tables	= stbl->nr_tables;
	}

	if (!config_tables)
		error("EFI config tables not found.");

	return __efi_get_rsdp_addr(config_tables, nr_tables, efi_64);
#else
	return 0;
#endif
}