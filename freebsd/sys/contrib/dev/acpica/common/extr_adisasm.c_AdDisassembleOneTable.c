#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* ShortDescription; } ;
struct TYPE_11__ {char* Filename; } ;
struct TYPE_10__ {char* Signature; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OWNER_ID ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IS_DATA_TABLE ; 
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  AE_OK ; 
 size_t ASL_FILE_MAP_OUTPUT ; 
 int /*<<< orphan*/  AcpiDmConvertParseObjects (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmCrossReferenceNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmDumpDataTable (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiDmDumpTree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmFindOrphanMethods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmFinishNamespaceLoad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiDmGetUnresolvedExternalMethodCount () ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiGbl_CaptureComments ; 
 scalar_t__ AcpiGbl_DmOpt_Disasm ; 
 int /*<<< orphan*/  AcpiGbl_ForceAmlDisassembly ; 
 int /*<<< orphan*/  AcpiGbl_ParseOpRoot ; 
 int /*<<< orphan*/  AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiGbl_TableSig ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiUtIsAmlTable (TYPE_1__*) ; 
 int /*<<< orphan*/  AdDisassemblerHeader (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdDisplayTables (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  AdParseTable (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdReparseOneTable (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ AslCompilerdebug ; 
 TYPE_3__* AslGbl_FileDescs ; 
 TYPE_2__* AslGbl_Files ; 
 scalar_t__ AslGbl_MapfileFlag ; 
 int CmGetFileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int FlGetFileSize (size_t) ; 
 int /*<<< orphan*/  NsDisplayNamespace () ; 
 int /*<<< orphan*/  NsSetupNamespaceListing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AdDisassembleOneTable (
    ACPI_TABLE_HEADER       *Table,
    FILE                    *File,
    char                    *Filename,
    char                    *DisasmFilename)
{
    ACPI_STATUS             Status;
    ACPI_OWNER_ID           OwnerId;


#ifdef ACPI_ASL_COMPILER

    /*
     * For ASL-/ASL+ converter: replace the temporary "XXXX"
     * table signature with the original. This "XXXX" makes
     * it harder for the AML interpreter to run the badaml
     * (.xxx) file produced from the converter in case if
     * it fails to get deleted.
     */
    if (AcpiGbl_CaptureComments)
    {
        strncpy (Table->Signature, AcpiGbl_TableSig, ACPI_NAMESEG_SIZE);
    }
#endif

    /* ForceAmlDisassembly means to assume the table contains valid AML */

    if (!AcpiGbl_ForceAmlDisassembly && !AcpiUtIsAmlTable (Table))
    {
        AdDisassemblerHeader (Filename, ACPI_IS_DATA_TABLE);

        /* This is a "Data Table" (non-AML table) */

        AcpiOsPrintf (" * ACPI Data Table [%4.4s]\n *\n",
            Table->Signature);
        AcpiOsPrintf (" * Format: [HexOffset DecimalOffset ByteLength]  "
            "FieldName : FieldValue\n */\n\n");

        AcpiDmDumpDataTable (Table);
        fprintf (stderr, "Acpi Data Table [%4.4s] decoded\n",
            Table->Signature);

        if (File)
        {
            fprintf (stderr, "Formatted output:  %s - %u bytes\n",
                DisasmFilename, CmGetFileSize (File));
        }

        return (AE_OK);
    }

    /*
     * This is an AML table (DSDT or SSDT).
     * Always parse the tables, only option is what to display
     */
    Status = AdParseTable (Table, &OwnerId, TRUE, FALSE);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not parse ACPI tables, %s\n",
            AcpiFormatException (Status));
        return (Status);
    }

    /* Debug output, namespace and parse tree */

    if (AslCompilerdebug && File)
    {
        AcpiOsPrintf ("/**** Before second load\n");

        NsSetupNamespaceListing (File);
        NsDisplayNamespace ();

        AcpiOsPrintf ("*****/\n");
    }

    /* Load namespace from names created within control methods */

    AcpiDmFinishNamespaceLoad (AcpiGbl_ParseOpRoot,
        AcpiGbl_RootNode, OwnerId);

    /*
     * Cross reference the namespace here, in order to
     * generate External() statements
     */
    AcpiDmCrossReferenceNamespace (AcpiGbl_ParseOpRoot,
        AcpiGbl_RootNode, OwnerId);

    if (AslCompilerdebug)
    {
        AcpiDmDumpTree (AcpiGbl_ParseOpRoot);
    }

    /* Find possible calls to external control methods */

    AcpiDmFindOrphanMethods (AcpiGbl_ParseOpRoot);

    /*
     * If we found any external control methods, we must reparse
     * the entire tree with the new information (namely, the
     * number of arguments per method)
     */
    if (AcpiDmGetUnresolvedExternalMethodCount ())
    {
        Status = AdReparseOneTable (Table, File, OwnerId);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
    }

    /*
     * Now that the namespace is finalized, we can perform namespace
     * transforms.
     *
     * 1) Convert fixed-offset references to resource descriptors
     *    to symbolic references (Note: modifies namespace)
     */
    AcpiDmConvertParseObjects (AcpiGbl_ParseOpRoot, AcpiGbl_RootNode);

    /* Optional displays */

    if (AcpiGbl_DmOpt_Disasm)
    {
        /* This is the real disassembly */

        AdDisplayTables (Filename, Table);

        /* Dump hex table if requested (-vt) */

        AcpiDmDumpDataTable (Table);

        fprintf (stderr, "Disassembly completed\n");
        if (File)
        {
            fprintf (stderr, "ASL Output:    %s - %u bytes\n",
                DisasmFilename, CmGetFileSize (File));
        }

        if (AslGbl_MapfileFlag)
        {
            fprintf (stderr, "%14s %s - %u bytes\n",
                AslGbl_FileDescs[ASL_FILE_MAP_OUTPUT].ShortDescription,
                AslGbl_Files[ASL_FILE_MAP_OUTPUT].Filename,
                FlGetFileSize (ASL_FILE_MAP_OUTPUT));
        }
    }

    return (AE_OK);
}