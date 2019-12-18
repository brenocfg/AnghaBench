#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_3__ {char* Signature; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 scalar_t__ bootverbose ; 
 TYPE_1__* pmap_mapbios (scalar_t__,int) ; 
 int /*<<< orphan*/  pmap_unmapbios (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
probe_table(vm_paddr_t address, const char *sig)
{
	ACPI_TABLE_HEADER *table;

	table = pmap_mapbios(address, sizeof(ACPI_TABLE_HEADER));
	if (table == NULL) {
		if (bootverbose)
			printf("ACPI: Failed to map table at 0x%jx\n",
			    (uintmax_t)address);
		return (0);
	}
	if (bootverbose)
		printf("Table '%.4s' at 0x%jx\n", table->Signature,
		    (uintmax_t)address);

	if (strncmp(table->Signature, sig, ACPI_NAMESEG_SIZE) != 0) {
		pmap_unmapbios((vm_offset_t)table, sizeof(ACPI_TABLE_HEADER));
		return (0);
	}
	pmap_unmapbios((vm_offset_t)table, sizeof(ACPI_TABLE_HEADER));
	return (1);
}