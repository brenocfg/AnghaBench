#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* Next; int /*<<< orphan*/  Table; } ;
struct TYPE_8__ {int /*<<< orphan*/  OemTableId; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_NEW_TABLE_DESC ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ACPI_GET_ALL_TABLES ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcDeleteTableList (TYPE_2__*) ; 
 int /*<<< orphan*/  AcGetAllTablesFromFile (char*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_DmOpt_Disasm ; 
 int /*<<< orphan*/  AcpiGbl_ForceAmlDisassembly ; 
 int /*<<< orphan*/ * AcpiGbl_ParseOpRoot ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiOsRedirectOutput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiPsDeleteParseTree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtIsAmlTable (TYPE_1__*) ; 
 int /*<<< orphan*/  AdDisassembleOneTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  AdDoExternalFileList (char*) ; 
 char* AdGenerateFilename (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdGetLocalTables () ; 
 int /*<<< orphan*/  FILE_SUFFIX_DISASSEMBLY ; 
 char* FlGenerateFilename (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 

ACPI_STATUS
AdAmlDisassemble (
    BOOLEAN                 OutToFile,
    char                    *Filename,
    char                    *Prefix,
    char                    **OutFilename)
{
    ACPI_STATUS             Status;
    char                    *DisasmFilename = NULL;
    FILE                    *File = NULL;
    ACPI_TABLE_HEADER       *Table = NULL;
    ACPI_NEW_TABLE_DESC     *ListHead = NULL;


    /*
     * Input: AML code from either a file or via GetTables (memory or
     * registry)
     */
    if (Filename)
    {
        /* Get the list of all AML tables in the file */

        Status = AcGetAllTablesFromFile (Filename,
            ACPI_GET_ALL_TABLES, &ListHead);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("Could not get ACPI tables from %s, %s\n",
                Filename, AcpiFormatException (Status));
            return (Status);
        }

        /* Process any user-specified files for external objects */

        Status = AdDoExternalFileList (Filename);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
    }
    else
    {
        Status = AdGetLocalTables ();
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("Could not get ACPI tables, %s\n",
                AcpiFormatException (Status));
            return (Status);
        }

        if (!AcpiGbl_DmOpt_Disasm)
        {
            return (AE_OK);
        }

        /* Obtained the local tables, just disassemble the DSDT */

        Status = AcpiGetTable (ACPI_SIG_DSDT, 0, &Table);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("Could not get DSDT, %s\n",
                AcpiFormatException (Status));
            return (Status);
        }

        AcpiOsPrintf ("\nDisassembly of DSDT\n");
        Prefix = AdGenerateFilename ("dsdt", Table->OemTableId);
    }

    /*
     * Output: ASL code. Redirect to a file if requested
     */
    if (OutToFile)
    {
        /* Create/Open a disassembly output file */

        DisasmFilename = FlGenerateFilename (Prefix, FILE_SUFFIX_DISASSEMBLY);
        if (!DisasmFilename)
        {
            fprintf (stderr, "Could not generate output filename\n");
            Status = AE_ERROR;
            goto Cleanup;
        }

        File = fopen (DisasmFilename, "w+");
        if (!File)
        {
            fprintf (stderr, "Could not open output file %s\n",
                DisasmFilename);
            Status = AE_ERROR;
            goto Cleanup;
        }

        AcpiOsRedirectOutput (File);
    }

    *OutFilename = DisasmFilename;

    /* Disassemble all AML tables within the file */

    while (ListHead)
    {
        Status = AdDisassembleOneTable (ListHead->Table,
            File, Filename, DisasmFilename);
        if (ACPI_FAILURE (Status))
        {
            break;
        }

        ListHead = ListHead->Next;
    }

Cleanup:

    if (Table &&
        !AcpiGbl_ForceAmlDisassembly &&
        !AcpiUtIsAmlTable (Table))
    {
        ACPI_FREE (Table);
    }

    AcDeleteTableList (ListHead);

    if (File)
    {
        fclose (File);
        AcpiOsRedirectOutput (stdout);
    }

    AcpiPsDeleteParseTree (AcpiGbl_ParseOpRoot);
    AcpiGbl_ParseOpRoot = NULL;
    return (Status);
}