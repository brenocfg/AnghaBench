#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_8__ {scalar_t__ XFacs; scalar_t__ Facs; scalar_t__ XDsdt; } ;
struct TYPE_7__ {TYPE_1__* Tables; } ;
struct TYPE_6__ {int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL ; 
 int /*<<< orphan*/  AcpiGbl_DsdtIndex ; 
 TYPE_5__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiGbl_FacsIndex ; 
 size_t AcpiGbl_FadtIndex ; 
 int /*<<< orphan*/  AcpiGbl_ReducedHardware ; 
 TYPE_4__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  AcpiGbl_XFacsIndex ; 
 int /*<<< orphan*/  AcpiTbCreateLocalFadt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTbGetTable (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiTbInstallStandardTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbPutTable (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiTbVerifyChecksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

void
AcpiTbParseFadt (
    void)
{
    UINT32                  Length;
    ACPI_TABLE_HEADER       *Table;
    ACPI_TABLE_DESC         *FadtDesc;
    ACPI_STATUS             Status;


    /*
     * The FADT has multiple versions with different lengths,
     * and it contains pointers to both the DSDT and FACS tables.
     *
     * Get a local copy of the FADT and convert it to a common format
     * Map entire FADT, assumed to be smaller than one page.
     */
    FadtDesc = &AcpiGbl_RootTableList.Tables[AcpiGbl_FadtIndex];
    Status = AcpiTbGetTable (FadtDesc, &Table);
    if (ACPI_FAILURE (Status))
    {
        return;
    }
    Length = FadtDesc->Length;

    /*
     * Validate the FADT checksum before we copy the table. Ignore
     * checksum error as we want to try to get the DSDT and FACS.
     */
    (void) AcpiTbVerifyChecksum (Table, Length);

    /* Create a local copy of the FADT in common ACPI 2.0+ format */

    AcpiTbCreateLocalFadt (Table, Length);

    /* All done with the real FADT, unmap it */

    AcpiTbPutTable (FadtDesc);

    /* Obtain the DSDT and FACS tables via their addresses within the FADT */

    AcpiTbInstallStandardTable (
        (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.XDsdt,
        ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL, FALSE, TRUE,
        &AcpiGbl_DsdtIndex);

    /* If Hardware Reduced flag is set, there is no FACS */

    if (!AcpiGbl_ReducedHardware)
    {
        if (AcpiGbl_FADT.Facs)
        {
            AcpiTbInstallStandardTable (
                (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.Facs,
                ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL, FALSE, TRUE,
                &AcpiGbl_FacsIndex);
        }
        if (AcpiGbl_FADT.XFacs)
        {
            AcpiTbInstallStandardTable (
                (ACPI_PHYSICAL_ADDRESS) AcpiGbl_FADT.XFacs,
                ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL, FALSE, TRUE,
                &AcpiGbl_XFacsIndex);
        }
    }
}