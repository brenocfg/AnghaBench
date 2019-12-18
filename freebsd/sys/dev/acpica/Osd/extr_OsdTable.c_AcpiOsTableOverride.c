#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_5__ {int /*<<< orphan*/ * Signature; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SUPPORT ; 
 int /*<<< orphan*/  AcpiGbl_DisableSsdtTableInstall ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* preload_fetch_addr (int /*<<< orphan*/ *) ; 
 size_t preload_fetch_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * preload_search_by_type (char*) ; 
 char tolower (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiOsTableOverride(ACPI_TABLE_HEADER *ExistingTable,
    ACPI_TABLE_HEADER **NewTable)
{
	char modname[] = "acpi_dsdt";
	caddr_t acpi_table;
	ACPI_TABLE_HEADER *hdr;
	size_t sz;

	if (ExistingTable == NULL || NewTable == NULL)
		return (AE_BAD_PARAMETER);

	*NewTable = NULL;
	if (!ACPI_COMPARE_NAMESEG(ExistingTable->Signature, ACPI_SIG_DSDT))
#ifdef notyet
		for (int i = 0; i < ACPI_NAMESEG_SIZE; i++)
			modname[i + 5] = tolower(ExistingTable->Signature[i]);
#else
		return (AE_SUPPORT);
#endif
	acpi_table = preload_search_by_type(modname);
	if (acpi_table == NULL)
		return (AE_NOT_FOUND);
	hdr = preload_fetch_addr(acpi_table);
	sz = preload_fetch_size(acpi_table);
	if (hdr == NULL || sz == 0)
		return (AE_ERROR);
#ifndef notyet
	/* Assume SSDT is installed with DSDT. */
	AcpiGbl_DisableSsdtTableInstall = TRUE;
#endif
	*NewTable = hdr;
	return (AE_OK);
}