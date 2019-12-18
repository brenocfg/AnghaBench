#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
struct TYPE_9__ {char* Signature; int Length; } ;
typedef  int INT32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  AcCheckTextModeCorruption (TYPE_1__*) ; 
 int /*<<< orphan*/  AcValidateTableHeader (int /*<<< orphan*/ *,long) ; 
 TYPE_1__* AcpiOsAllocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiTbVerifyChecksum (TYPE_1__*,int) ; 
 int /*<<< orphan*/  AcpiUtIsAmlTable (TYPE_1__*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int fread (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static ACPI_STATUS
AcGetOneTableFromFile (
    char                    *Filename,
    FILE                    *File,
    UINT8                   GetOnlyAmlTables,
    ACPI_TABLE_HEADER       **ReturnTable)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_TABLE_HEADER       TableHeader;
    ACPI_TABLE_HEADER       *Table;
    INT32                   Count;
    long                    TableOffset;


    *ReturnTable = NULL;

    /* Get the table header to examine signature and length */

    TableOffset = ftell (File);
    Count = fread (&TableHeader, 1, sizeof (ACPI_TABLE_HEADER), File);
    if (Count != sizeof (ACPI_TABLE_HEADER))
    {
        return (AE_CTRL_TERMINATE);
    }

    if (GetOnlyAmlTables)
    {
        /* Validate the table signature/header (limited ASCII chars) */

        Status = AcValidateTableHeader (File, TableOffset);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        /*
         * Table must be an AML table (DSDT/SSDT).
         * Used for iASL -e option only.
         */
        if (!AcpiUtIsAmlTable (&TableHeader))
        {
            fprintf (stderr,
                "    %s: Table [%4.4s] is not an AML table - ignoring\n",
                Filename, TableHeader.Signature);

            return (AE_TYPE);
        }
    }

    /* Allocate a buffer for the entire table */

    Table = AcpiOsAllocate ((ACPI_SIZE) TableHeader.Length);
    if (!Table)
    {
        return (AE_NO_MEMORY);
    }

    /* Read the entire ACPI table, including header */

    fseek (File, TableOffset, SEEK_SET);

    Count = fread (Table, 1, TableHeader.Length, File);

    /*
     * Checks for data table headers happen later in the execution. Only verify
     * for Aml tables at this point in the code.
     */
    if (GetOnlyAmlTables && Count != (INT32) TableHeader.Length)
    {
        Status = AE_ERROR;
        goto ErrorExit;
    }

    /* Validate the checksum (just issue a warning) */

    Status = AcpiTbVerifyChecksum (Table, TableHeader.Length);
    if (ACPI_FAILURE (Status))
    {
        Status = AcCheckTextModeCorruption (Table);
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }
    }

    *ReturnTable = Table;
    return (AE_OK);


ErrorExit:
    AcpiOsFree (Table);
    return (Status);
}