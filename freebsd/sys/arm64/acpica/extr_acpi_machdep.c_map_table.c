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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  void* vm_offset_t ;
struct TYPE_2__ {void* Length; int /*<<< orphan*/  Signature; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  AcpiTbChecksum (void*,void*) ; 
 scalar_t__ bootverbose ; 
 void* pmap_mapbios (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pmap_unmapbios (void*,void*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
map_table(vm_paddr_t pa, int offset, const char *sig)
{
	ACPI_TABLE_HEADER *header;
	vm_offset_t length;
	void *table;

	header = pmap_mapbios(pa, sizeof(ACPI_TABLE_HEADER));
	if (strncmp(header->Signature, sig, ACPI_NAMESEG_SIZE) != 0) {
		pmap_unmapbios((vm_offset_t)header, sizeof(ACPI_TABLE_HEADER));
		return (NULL);
	}
	length = header->Length;
	pmap_unmapbios((vm_offset_t)header, sizeof(ACPI_TABLE_HEADER));

	table = pmap_mapbios(pa, length);
	if (ACPI_FAILURE(AcpiTbChecksum(table, length))) {
		if (bootverbose)
			printf("ACPI: Failed checksum for table %s\n", sig);
#if (ACPI_CHECKSUM_ABORT)
		pmap_unmapbios(table, length);
		return (NULL);
#endif
	}
	return (table);
}