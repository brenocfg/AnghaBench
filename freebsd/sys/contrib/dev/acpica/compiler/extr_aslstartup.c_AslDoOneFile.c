#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_6__ {int /*<<< orphan*/  Filename; } ;
struct TYPE_5__ {int FileType; int /*<<< orphan*/  TotalLineCount; int /*<<< orphan*/  OriginalInputFileSize; } ;
typedef  TYPE_1__ ASL_GLOBAL_FILE_NODE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 size_t ASL_FILE_INPUT ; 
 int /*<<< orphan*/  ASL_FILE_STDERR ; 
#define  ASL_INPUT_TYPE_ASCII_ASL 131 
#define  ASL_INPUT_TYPE_ASCII_DATA 130 
#define  ASL_INPUT_TYPE_BINARY 129 
#define  ASL_INPUT_TYPE_BINARY_ACPI_TABLE 128 
 int /*<<< orphan*/  AcpiGbl_DisasmFlag ; 
 int /*<<< orphan*/  AeClearErrorLog () ; 
 int /*<<< orphan*/  AePrintErrorLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslCheckForErrorExit () ; 
 int AslDetectSourceFileType (TYPE_3__*) ; 
 int /*<<< orphan*/  AslDoDisassembly () ; 
 int /*<<< orphan*/  AslGbl_CurrentLineNumber ; 
 int /*<<< orphan*/  AslGbl_DirectoryPath ; 
 int /*<<< orphan*/  AslGbl_DoCompile ; 
 int AslGbl_FileType ; 
 TYPE_3__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_OutputFilenamePrefix ; 
 int /*<<< orphan*/ * AslGbl_Signature ; 
 scalar_t__ AslGbl_UseDefaultAmlFilename ; 
 int /*<<< orphan*/  AslInitializeGlobals () ; 
 int /*<<< orphan*/  CmDoCompile () ; 
 int /*<<< orphan*/  DtDoCompile () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlCloseFile (size_t) ; 
 TYPE_1__* FlGetCurrentFileNode () ; 
 int /*<<< orphan*/  FlGetFileSize (size_t) ; 
 int /*<<< orphan*/  FlInitOneFile (char*) ; 
 int /*<<< orphan*/  FlOpenAmlOutputFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlOpenInputFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlOpenMiscOutputFiles (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlSplitInputPathname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrInitializeGlobals () ; 
 int /*<<< orphan*/  PrTerminatePreprocessor () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UtBeginEvent (char*) ; 
 int /*<<< orphan*/  UtConvertBackslashes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtEndEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtLocalCacheCalloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

ACPI_STATUS
AslDoOneFile (
    char                    *Filename)
{
    ACPI_STATUS             Status;
    UINT8                   Event;
    ASL_GLOBAL_FILE_NODE    *FileNode;


    /* Re-initialize "some" compiler/preprocessor globals */

    AslInitializeGlobals ();
    PrInitializeGlobals ();

    /*
     * Extract the directory path. This path is used for possible include
     * files and the optional AML filename embedded in the input file
     * DefinitionBlock declaration.
     */
    Status = FlSplitInputPathname (Filename, &AslGbl_DirectoryPath, NULL);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /*
     * There was an input file detected at this point. Each input ASL file is
     * associated with one global file node consisting of the input file and
     * all output files associated with it. This is useful when compiling
     * multiple files in one command.
     */
    Status = FlInitOneFile(Filename);
    if (ACPI_FAILURE (Status))
    {
        return (AE_ERROR);
    }

    /* Take a copy of the input filename, convert any backslashes */

    AslGbl_Files[ASL_FILE_INPUT].Filename =
        UtLocalCacheCalloc (strlen (Filename) + 1);

    strcpy (AslGbl_Files[ASL_FILE_INPUT].Filename, Filename);
    UtConvertBackslashes (AslGbl_Files[ASL_FILE_INPUT].Filename);

    /*
     * Open the input file. Here, this should be an ASCII source file,
     * either an ASL file or a Data Table file
     */
    Status = FlOpenInputFile (AslGbl_Files[ASL_FILE_INPUT].Filename);
    if (ACPI_FAILURE (Status))
    {
        AePrintErrorLog (ASL_FILE_STDERR);
        return (AE_ERROR);
    }

    FileNode = FlGetCurrentFileNode();
    if (!FileNode)
    {
        return (AE_ERROR);
    }

    FileNode->OriginalInputFileSize = FlGetFileSize (ASL_FILE_INPUT);

    /* Determine input file type */

    AslGbl_FileType = AslDetectSourceFileType (&AslGbl_Files[ASL_FILE_INPUT]);
    FileNode->FileType = AslGbl_FileType;
    if (AslGbl_FileType == ASL_INPUT_TYPE_BINARY)
    {
        return (AE_ERROR);
    }

    /*
     * If -p not specified, we will use the input filename as the
     * output filename prefix
     */
    if (AslGbl_UseDefaultAmlFilename)
    {
        AslGbl_OutputFilenamePrefix = AslGbl_Files[ASL_FILE_INPUT].Filename;
    }

    /*
     * Open the output file. Note: by default, the name of this file comes from
     * the table descriptor within the input file.
     */
    if (AslGbl_FileType == ASL_INPUT_TYPE_ASCII_ASL)
    {
        Event = UtBeginEvent ("Open AML output file");
        Status = FlOpenAmlOutputFile (AslGbl_OutputFilenamePrefix);
        UtEndEvent (Event);
        if (ACPI_FAILURE (Status))
        {
            AePrintErrorLog (ASL_FILE_STDERR);
            return (AE_ERROR);
        }
    }

    /* Open the optional output files (listings, etc.) */

    Status = FlOpenMiscOutputFiles (AslGbl_OutputFilenamePrefix);
    if (ACPI_FAILURE (Status))
    {
        AePrintErrorLog (ASL_FILE_STDERR);
        return (AE_ERROR);
    }

    /*
     * Compilation of ASL source versus DataTable source uses different
     * compiler subsystems
     */
    switch (AslGbl_FileType)
    {
    /*
     * Data Table Compilation
     */
    case ASL_INPUT_TYPE_ASCII_DATA:

        Status = DtDoCompile ();
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        if (AslGbl_Signature)
        {
            AslGbl_Signature = NULL;
        }

        /* Check if any errors occurred during compile */

        Status = AslCheckForErrorExit ();
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        /* Cleanup (for next source file) and exit */

        AeClearErrorLog ();
        PrTerminatePreprocessor ();
        return (Status);

    /*
     * ASL Compilation
     */
    case ASL_INPUT_TYPE_ASCII_ASL:

        Status = CmDoCompile ();
        if (ACPI_FAILURE (Status))
        {
            PrTerminatePreprocessor ();
            return (Status);
        }

        /*
         * At this point, we know how many lines are in the input file. Save it
         * to display for post-compilation summary.
         */
        FileNode->TotalLineCount = AslGbl_CurrentLineNumber;
        return (AE_OK);

    /*
     * Binary ACPI table was auto-detected, disassemble it
     */
    case ASL_INPUT_TYPE_BINARY_ACPI_TABLE:

        /* We have what appears to be an ACPI table, disassemble it */

        FlCloseFile (ASL_FILE_INPUT);
        AslGbl_DoCompile = FALSE;
        AcpiGbl_DisasmFlag = TRUE;
        Status = AslDoDisassembly ();
        return (Status);

    /* Unknown binary table */

    case ASL_INPUT_TYPE_BINARY:

        AePrintErrorLog (ASL_FILE_STDERR);
        return (AE_ERROR);

    default:

        printf ("Unknown file type %X\n", AslGbl_FileType);
        return (AE_ERROR);
    }
}