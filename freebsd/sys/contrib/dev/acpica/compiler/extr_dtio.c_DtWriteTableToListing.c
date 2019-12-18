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
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  Handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_RAW_TABLE_DATA_HEADER ; 
 int /*<<< orphan*/  ASL_FILE_AML_OUTPUT ; 
 size_t ASL_FILE_LISTING_OUTPUT ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsRedirectOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtDumpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_ListingFlag ; 
 int /*<<< orphan*/  AslGbl_TableLength ; 
 int /*<<< orphan*/  DB_BYTE_DISPLAY ; 
 int /*<<< orphan*/  FlReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlSeekFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * UtLocalCalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void
DtWriteTableToListing (
    void)
{
    UINT8                   *Buffer;


    if (!AslGbl_ListingFlag)
    {
        return;
    }

    /* Read the entire table from the output file */

    Buffer = UtLocalCalloc (AslGbl_TableLength);
    FlSeekFile (ASL_FILE_AML_OUTPUT, 0);
    FlReadFile (ASL_FILE_AML_OUTPUT, Buffer, AslGbl_TableLength);

    /* Dump the raw table data */

    AcpiOsRedirectOutput (AslGbl_Files[ASL_FILE_LISTING_OUTPUT].Handle);

    AcpiOsPrintf ("\n%s: Length %d (0x%X)\n\n",
        ACPI_RAW_TABLE_DATA_HEADER, AslGbl_TableLength, AslGbl_TableLength);
    AcpiUtDumpBuffer (Buffer, AslGbl_TableLength, DB_BYTE_DISPLAY, 0);

    AcpiOsRedirectOutput (stdout);
    ACPI_FREE (Buffer);
}