#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
struct TYPE_4__ {struct TYPE_4__* Next; int /*<<< orphan*/ * Table; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_1__ ACPI_NEW_TABLE_DESC ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 int ACPI_UINT32_MAX ; 
 scalar_t__ AE_BAD_HEADER ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 scalar_t__ AE_ERROR ; 
 scalar_t__ AE_NOT_EXIST ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AE_TYPE ; 
 scalar_t__ AcGetOneTableFromFile (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcIsFileBinary (int /*<<< orphan*/ *) ; 
 TYPE_1__* AcpiOsAllocate (int) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbPrintTableHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CmGetFileSize (int /*<<< orphan*/ *) ; 
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

ACPI_STATUS
AcGetAllTablesFromFile (
    char                    *Filename,
    UINT8                   GetOnlyAmlTables,
    ACPI_NEW_TABLE_DESC     **ReturnListHead)
{
    ACPI_NEW_TABLE_DESC     *ListHead = NULL;
    ACPI_NEW_TABLE_DESC     *ListTail = NULL;
    ACPI_NEW_TABLE_DESC     *TableDesc;
    FILE                    *File;
    ACPI_TABLE_HEADER       *Table = NULL;
    UINT32                  FileSize;
    ACPI_STATUS             Status = AE_OK;


    File = fopen (Filename, "rb");
    if (!File)
    {
        fprintf (stderr, "Could not open input file: %s\n", Filename);
        if (errno == ENOENT)
        {
            return (AE_NOT_EXIST);
        }

        return (AE_ERROR);
    }

    /* Get the file size */

    FileSize = CmGetFileSize (File);
    if (FileSize == ACPI_UINT32_MAX)
    {
        Status = AE_ERROR;
        goto Exit;
    }

    fprintf (stderr,
        "Input file %s, Length 0x%X (%u) bytes\n",
        Filename, FileSize, FileSize);

    /* We must have at least one ACPI table header */

    if (FileSize < sizeof (ACPI_TABLE_HEADER))
    {
        Status = AE_BAD_HEADER;
        goto Exit;
    }

    /* Check for an non-binary file */

    if (!AcIsFileBinary (File))
    {
        fprintf (stderr,
            "    %s: File does not appear to contain a valid AML table\n",
            Filename);
        Status = AE_TYPE;
        goto Exit;
    }

    /* Read all tables within the file */

    while (ACPI_SUCCESS (Status))
    {
        /* Get one entire ACPI table */

        Status = AcGetOneTableFromFile (
            Filename, File, GetOnlyAmlTables, &Table);

        if (Status == AE_CTRL_TERMINATE)
        {
            Status = AE_OK;
            break;
        }
        else if (Status == AE_TYPE)
        {
            Status = AE_OK;
            goto Exit;
        }
        else if (ACPI_FAILURE (Status))
        {
            goto Exit;
        }

        /* Print table header for iASL/disassembler only */

#ifdef ACPI_ASL_COMPILER

        AcpiTbPrintTableHeader (0, Table);
#endif

        /* Allocate and link a table descriptor */

        TableDesc = AcpiOsAllocate (sizeof (ACPI_NEW_TABLE_DESC));
        if (!TableDesc)
        {
            AcpiOsFree (Table);
            Status = AE_NO_MEMORY;
            goto Exit;
        }

        TableDesc->Table = Table;
        TableDesc->Next = NULL;

        /* Link at the end of the local table list */

        if (!ListHead)
        {
            ListHead = TableDesc;
            ListTail = TableDesc;
        }
        else
        {
            ListTail->Next = TableDesc;
            ListTail = TableDesc;
        }
    }

    /* Add the local table list to the end of the global list */

    if (*ReturnListHead)
    {
        ListTail = *ReturnListHead;
        while (ListTail->Next)
        {
            ListTail = ListTail->Next;
        }

        ListTail->Next = ListHead;
    }
    else
    {
        *ReturnListHead = ListHead;
    }

Exit:
    fclose(File);
    return (Status);
}