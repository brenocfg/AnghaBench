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
typedef  int UINT32 ;
struct TYPE_3__ {int /*<<< orphan*/  Template; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_DMTABLE_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ACPI_COMMON_HEADER (char*,char*) ; 
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_RSDP_NAME ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  ACPI_SIG_FACS ; 
 int /*<<< orphan*/  ACPI_SIG_OSDT ; 
 int /*<<< orphan*/  ACPI_SIG_SSDT ; 
 int /*<<< orphan*/  ACPI_TABLE_HEADER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDmDumpDataTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiOsRedirectOutput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtStrlwr (char*) ; 
 scalar_t__ AslGbl_VerboseTemplates ; 
 int DtEmitDefinitionBlock (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FILE_SUFFIX_ASL_CODE ; 
 char* FlGenerateFilename (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TemplateFacs ; 
 int /*<<< orphan*/  TemplateRsdp ; 
 int /*<<< orphan*/  UtQueryForOverwrite (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static ACPI_STATUS
DtCreateOneTemplate (
    char                    *Signature,
    UINT32                  TableCount,
    const ACPI_DMTABLE_DATA  *TableData)
{
    char                    *DisasmFilename;
    FILE                    *File;
    ACPI_STATUS             Status = AE_OK;
    int                     Actual;
    UINT32                  i;


    /* New file will have a .asl suffix */

    DisasmFilename = FlGenerateFilename (
        Signature, FILE_SUFFIX_ASL_CODE);
    if (!DisasmFilename)
    {
        fprintf (stderr, "Could not generate output filename\n");
        return (AE_ERROR);
    }

    AcpiUtStrlwr (DisasmFilename);
    if (!UtQueryForOverwrite (DisasmFilename))
    {
        return (AE_OK);
    }

    File = fopen (DisasmFilename, "w+");
    if (!File)
    {
        fprintf (stderr, "Could not open output file %s\n",
            DisasmFilename);
        return (AE_ERROR);
    }

    /* Emit the common file header */

    AcpiOsRedirectOutput (File);

    AcpiOsPrintf ("/*\n");
    AcpiOsPrintf (ACPI_COMMON_HEADER ("iASL Compiler/Disassembler", " * "));

    if (TableCount == 0)
    {
        AcpiOsPrintf (" * Template for [%4.4s] ACPI Table",
            Signature);
    }
    else
    {
        AcpiOsPrintf (" * Template for [%4.4s] and %u [SSDT] ACPI Tables",
            Signature, TableCount);
    }

    /* Dump the actual ACPI table */

    if (TableData)
    {
        /* Normal case, tables that appear in AcpiDmTableData */

        AcpiOsPrintf (" (static data table)\n");

        if (AslGbl_VerboseTemplates)
        {
            AcpiOsPrintf (" * Format: [HexOffset DecimalOffset ByteLength]"
                "  FieldName : HexFieldValue\n */\n\n");
        }
        else
        {
            AcpiOsPrintf (" * Format: [ByteLength]"
                "  FieldName : HexFieldValue\n */\n");
        }

        AcpiDmDumpDataTable (ACPI_CAST_PTR (ACPI_TABLE_HEADER,
            TableData->Template));
    }
    else
    {
        /* Special ACPI tables - DSDT, SSDT, OSDT, FACS, RSDP */

        AcpiOsPrintf (" (AML byte code table)\n");
        AcpiOsPrintf (" */\n");

        if (ACPI_COMPARE_NAMESEG (Signature, ACPI_SIG_DSDT))
        {
            Actual = DtEmitDefinitionBlock (
                File, DisasmFilename, ACPI_SIG_DSDT, 1);
            if (Actual < 0)
            {
                Status = AE_ERROR;
                goto Cleanup;
            }

            /* Emit any requested SSDTs into the same file */

            for (i = 1; i <= TableCount; i++)
            {
                Actual = DtEmitDefinitionBlock (
                    File, DisasmFilename, ACPI_SIG_SSDT, i + 1);
                if (Actual < 0)
                {
                    Status = AE_ERROR;
                    goto Cleanup;
                }
            }
        }
        else if (ACPI_COMPARE_NAMESEG (Signature, ACPI_SIG_SSDT))
        {
            Actual = DtEmitDefinitionBlock (
                File, DisasmFilename, ACPI_SIG_SSDT, 1);
            if (Actual < 0)
            {
                Status = AE_ERROR;
                goto Cleanup;
            }
        }
        else if (ACPI_COMPARE_NAMESEG (Signature, ACPI_SIG_OSDT))
        {
            Actual = DtEmitDefinitionBlock (
                File, DisasmFilename, ACPI_SIG_OSDT, 1);
            if (Actual < 0)
            {
                Status = AE_ERROR;
                goto Cleanup;
            }
        }
        else if (ACPI_COMPARE_NAMESEG (Signature, ACPI_SIG_FACS))
        {
            AcpiDmDumpDataTable (ACPI_CAST_PTR (ACPI_TABLE_HEADER,
                TemplateFacs));
        }
        else if (ACPI_COMPARE_NAMESEG (Signature, ACPI_RSDP_NAME))
        {
            AcpiDmDumpDataTable (ACPI_CAST_PTR (ACPI_TABLE_HEADER,
                TemplateRsdp));
        }
        else
        {
            fprintf (stderr,
                "%4.4s, Unrecognized ACPI table signature\n", Signature);
            Status = AE_ERROR;
            goto Cleanup;
        }
    }

    if (TableCount == 0)
    {
        fprintf (stderr,
            "Created ACPI table template for [%4.4s], "
            "written to \"%s\"\n",
            Signature, DisasmFilename);
    }
    else
    {
        fprintf (stderr,
            "Created ACPI table templates for [%4.4s] "
            "and %u [SSDT], written to \"%s\"\n",
            Signature, TableCount, DisasmFilename);
    }

Cleanup:
    fclose (File);
    AcpiOsRedirectOutput (stdout);
    return (Status);
}