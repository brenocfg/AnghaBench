#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  efi_guid_t ;
struct TYPE_3__ {int table; int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ efi_config_table_64_t ;
struct TYPE_4__ {int table; int /*<<< orphan*/  guid; } ;
typedef  TYPE_2__ efi_config_table_32_t ;
typedef  int acpi_physical_address ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_20_TABLE_GUID ; 
 int /*<<< orphan*/  ACPI_TABLE_GUID ; 
 int /*<<< orphan*/  CONFIG_X86_64 ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_putstr (char*) ; 
 int /*<<< orphan*/  efi_guidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_physical_address
__efi_get_rsdp_addr(unsigned long config_tables, unsigned int nr_tables,
		    bool efi_64)
{
	acpi_physical_address rsdp_addr = 0;

#ifdef CONFIG_EFI
	int i;

	/* Get EFI tables from systab. */
	for (i = 0; i < nr_tables; i++) {
		acpi_physical_address table;
		efi_guid_t guid;

		if (efi_64) {
			efi_config_table_64_t *tbl = (efi_config_table_64_t *)config_tables + i;

			guid  = tbl->guid;
			table = tbl->table;

			if (!IS_ENABLED(CONFIG_X86_64) && table >> 32) {
				debug_putstr("Error getting RSDP address: EFI config table located above 4GB.\n");
				return 0;
			}
		} else {
			efi_config_table_32_t *tbl = (efi_config_table_32_t *)config_tables + i;

			guid  = tbl->guid;
			table = tbl->table;
		}

		if (!(efi_guidcmp(guid, ACPI_TABLE_GUID)))
			rsdp_addr = table;
		else if (!(efi_guidcmp(guid, ACPI_20_TABLE_GUID)))
			return table;
	}
#endif
	return rsdp_addr;
}