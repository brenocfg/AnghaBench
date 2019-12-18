#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_5__ {char* Filename; int /*<<< orphan*/  Handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  OutputByteLength; int /*<<< orphan*/  TotalFields; int /*<<< orphan*/  ParserErrorDetected; int /*<<< orphan*/  OriginalInputFileSize; int /*<<< orphan*/  TotalLineCount; } ;
typedef  int /*<<< orphan*/  DT_FIELD ;
typedef  TYPE_1__ ASL_GLOBAL_FILE_NODE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 size_t ASL_FILE_AML_OUTPUT ; 
 size_t ASL_FILE_INPUT ; 
 int /*<<< orphan*/  ASL_MSG_SYNTAX ; 
 int /*<<< orphan*/  ASL_PARSE_OUTPUT ; 
 int /*<<< orphan*/  AslGbl_CurrentLineNumber ; 
 scalar_t__ AslGbl_DtLexBisonPrototype ; 
 int /*<<< orphan*/ * AslGbl_FieldList ; 
 TYPE_3__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_InputByteCount ; 
 int /*<<< orphan*/  AslGbl_InputFieldCount ; 
 int /*<<< orphan*/  AslGbl_OutputFilenamePrefix ; 
 scalar_t__ AslGbl_PreprocessFlag ; 
 scalar_t__ AslGbl_PreprocessOnly ; 
 int /*<<< orphan*/  AslGbl_RootTable ; 
 int /*<<< orphan*/  AslGbl_TableLength ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtCompileDataTable (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DtCompilerInitLexer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtCompilerParserparse () ; 
 int /*<<< orphan*/  DtCompilerTerminateLexer () ; 
 int /*<<< orphan*/  DtError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  DtInitialize () ; 
 int /*<<< orphan*/  DtOutputBinary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DtScanFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtWriteTableToListing () ; 
 TYPE_1__* FlGetCurrentFileNode () ; 
 int /*<<< orphan*/  FlOpenAmlOutputFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HxDoHexOutput () ; 
 int /*<<< orphan*/  PrDoPreprocess () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UtBeginEvent (char*) ; 
 int /*<<< orphan*/  UtEndEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

ACPI_STATUS
DtDoCompile (
    void)
{
    ACPI_STATUS             Status;
    UINT8                   Event;
    DT_FIELD                *FieldList;
    ASL_GLOBAL_FILE_NODE    *FileNode;


    /* Initialize globals */

    DtInitialize ();

    /* Preprocessor */

    if (AslGbl_PreprocessFlag)
    {
        /* Preprocessor */

        Event = UtBeginEvent ("Preprocess input file");
        PrDoPreprocess ();
        UtEndEvent (Event);

        if (AslGbl_PreprocessOnly)
        {
            return (AE_OK);
        }
    }

    /* Compile the parse tree */

    if (AslGbl_DtLexBisonPrototype)
    {
        Event = UtBeginEvent ("Parse data table in prototype mode");

        DtCompilerInitLexer (AslGbl_Files[ASL_FILE_INPUT].Handle);
        DtCompilerParserparse ();
        FieldList = AslGbl_FieldList;
        DtCompilerTerminateLexer ();

        UtEndEvent (Event);
    }
    else
    {
        /*
         * Scan the input file (file is already open) and
         * build the parse tree
         */
        Event = UtBeginEvent ("Scan and parse input file");
        FieldList = DtScanFile (AslGbl_Files[ASL_FILE_INPUT].Handle);
        UtEndEvent (Event);
    }

    /* Did the parse tree get successfully constructed? */

    if (!FieldList)
    {
        /* TBD: temporary error message. Msgs should come from function above */

        DtError (ASL_ERROR, ASL_MSG_SYNTAX, NULL,
            "Input file does not appear to be an ASL or data table source file");

        return (AE_ERROR);
    }

    Event = UtBeginEvent ("Compile parse tree");

    Status = DtCompileDataTable (&FieldList);
    UtEndEvent (Event);

    FileNode = FlGetCurrentFileNode ();
    if (!FileNode)
    {
        fprintf (stderr, "Summary for %s could not be generated",
            AslGbl_Files[ASL_FILE_INPUT].Filename);
    }
    else
    {
        FileNode->TotalLineCount = AslGbl_CurrentLineNumber;
        FileNode->OriginalInputFileSize = AslGbl_InputByteCount;
        DbgPrint (ASL_PARSE_OUTPUT, "Line count: %u input file size: %u\n",
                FileNode->TotalLineCount, FileNode->OriginalInputFileSize);
    }

    if (ACPI_FAILURE (Status))
    {
        if (FileNode)
        {
            FileNode->ParserErrorDetected = TRUE;
        }

        /* TBD: temporary error message. Msgs should come from function above */

        DtError (ASL_ERROR, ASL_MSG_SYNTAX, NULL,
            "Could not compile input file");

        return (Status);
    }

    /* Create/open the binary output file */

    AslGbl_Files[ASL_FILE_AML_OUTPUT].Filename = NULL;
    Status = FlOpenAmlOutputFile (AslGbl_OutputFilenamePrefix);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Write the binary, then the optional hex file */

    DtOutputBinary (AslGbl_RootTable);
    HxDoHexOutput ();
    DtWriteTableToListing ();

    /* Save the compile time statistics to the current file node */

    if (FileNode)
    {
        FileNode->TotalFields = AslGbl_InputFieldCount;
        FileNode->OutputByteLength = AslGbl_TableLength;
    }

    return (Status);
}