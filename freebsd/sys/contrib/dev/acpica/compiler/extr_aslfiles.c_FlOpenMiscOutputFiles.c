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
struct TYPE_2__ {char* Filename; int /*<<< orphan*/  Handle; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 size_t ASL_FILE_ASM_INCLUDE_OUTPUT ; 
 size_t ASL_FILE_ASM_SOURCE_OUTPUT ; 
 size_t ASL_FILE_CONV_DEBUG_OUTPUT ; 
 size_t ASL_FILE_C_INCLUDE_OUTPUT ; 
 size_t ASL_FILE_C_OFFSET_OUTPUT ; 
 size_t ASL_FILE_C_SOURCE_OUTPUT ; 
 size_t ASL_FILE_DEBUG_OUTPUT ; 
 size_t ASL_FILE_HEX_OUTPUT ; 
 size_t ASL_FILE_LISTING_OUTPUT ; 
 size_t ASL_FILE_MAP_OUTPUT ; 
 size_t ASL_FILE_NAMESPACE_OUTPUT ; 
 size_t ASL_FILE_PREPROCESSOR ; 
 size_t ASL_FILE_PREPROCESSOR_USER ; 
 size_t ASL_FILE_SOURCE_OUTPUT ; 
 size_t ASL_FILE_XREF_OUTPUT ; 
 scalar_t__ ASL_INPUT_TYPE_ASCII_DATA ; 
 scalar_t__ ASL_INPUT_TYPE_BINARY_ACPI_TABLE ; 
 int /*<<< orphan*/  ASL_MSG_DEBUG_FILENAME ; 
 int /*<<< orphan*/  ASL_MSG_LISTING_FILENAME ; 
 int /*<<< orphan*/  ASL_MSG_PREPROCESSOR_FILENAME ; 
 int /*<<< orphan*/  AcpiGbl_ConvDebugFile ; 
 scalar_t__ AcpiGbl_DebugAslConversion ; 
 int /*<<< orphan*/  AslCommonError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AslCompilerFileHeader (size_t) ; 
 int /*<<< orphan*/  AslCompilerSignon (size_t) ; 
 scalar_t__ AslGbl_AsmIncludeOutputFlag ; 
 scalar_t__ AslGbl_AsmOutputFlag ; 
 scalar_t__ AslGbl_C_IncludeOutputFlag ; 
 scalar_t__ AslGbl_C_OffsetTableFlag ; 
 scalar_t__ AslGbl_C_OutputFlag ; 
 scalar_t__ AslGbl_CrossReferenceOutput ; 
 scalar_t__ AslGbl_DebugFlag ; 
 scalar_t__ AslGbl_FileType ; 
 TYPE_1__* AslGbl_Files ; 
 scalar_t__ AslGbl_HexOutputFlag ; 
 scalar_t__ AslGbl_ListingFlag ; 
 scalar_t__ AslGbl_MapfileFlag ; 
 scalar_t__ AslGbl_NsOutputFlag ; 
 scalar_t__ AslGbl_PreprocessFlag ; 
 scalar_t__ AslGbl_PreprocessorOutputFlag ; 
 int /*<<< orphan*/  CmCleanupAndExit () ; 
 int /*<<< orphan*/  FILE_SUFFIX_ASM_INCLUDE ; 
 int /*<<< orphan*/  FILE_SUFFIX_ASM_SOURCE ; 
 int /*<<< orphan*/  FILE_SUFFIX_CONVERT_DEBUG ; 
 int /*<<< orphan*/  FILE_SUFFIX_C_INCLUDE ; 
 int /*<<< orphan*/  FILE_SUFFIX_C_OFFSET ; 
 int /*<<< orphan*/  FILE_SUFFIX_C_SOURCE ; 
 int /*<<< orphan*/  FILE_SUFFIX_DEBUG ; 
 int /*<<< orphan*/  FILE_SUFFIX_HEX_DUMP ; 
 int /*<<< orphan*/  FILE_SUFFIX_LISTING ; 
 int /*<<< orphan*/  FILE_SUFFIX_MAP ; 
 int /*<<< orphan*/  FILE_SUFFIX_NAMESPACE ; 
 int /*<<< orphan*/  FILE_SUFFIX_PREPROCESSOR ; 
 int /*<<< orphan*/  FILE_SUFFIX_PREPROC_USER ; 
 int /*<<< orphan*/  FILE_SUFFIX_SOURCE ; 
 int /*<<< orphan*/  FILE_SUFFIX_XREF ; 
 char* FlGenerateFilename (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlOpenFile (size_t,char*,char*) ; 
 int /*<<< orphan*/  FlPrintFile (size_t,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

ACPI_STATUS
FlOpenMiscOutputFiles (
    char                    *FilenamePrefix)
{
    char                    *Filename;


     /* Create/Open a map file if requested */

    if (AslGbl_MapfileFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_MAP);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the hex file, text mode (closed at compiler exit) */

        FlOpenFile (ASL_FILE_MAP_OUTPUT, Filename, "w+t");

        AslCompilerSignon (ASL_FILE_MAP_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_MAP_OUTPUT);
    }

    /* All done for disassembler */

    if (AslGbl_FileType == ASL_INPUT_TYPE_BINARY_ACPI_TABLE)
    {
        return (AE_OK);
    }

    /* Create/Open a hex output file if asked */

    if (AslGbl_HexOutputFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_HEX_DUMP);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the hex file, text mode */

        FlOpenFile (ASL_FILE_HEX_OUTPUT, Filename, "w+t");

        AslCompilerSignon (ASL_FILE_HEX_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_HEX_OUTPUT);
    }

    /* Create/Open a debug output file if asked */

    if (AslGbl_DebugFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_DEBUG);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_DEBUG_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the debug file as STDERR, text mode */

        AslGbl_Files[ASL_FILE_DEBUG_OUTPUT].Filename = Filename;
        AslGbl_Files[ASL_FILE_DEBUG_OUTPUT].Handle =
            freopen (Filename, "w+t", stderr);

        if (!AslGbl_Files[ASL_FILE_DEBUG_OUTPUT].Handle)
        {
            /*
             * A problem with freopen is that on error, we no longer
             * have stderr and cannot emit normal error messages.
             * Emit error to stdout, close files, and exit.
             */
            fprintf (stdout,
                "\nCould not open debug output file: %s\n\n", Filename);

            CmCleanupAndExit ();
            exit (1);
        }

        AslCompilerSignon (ASL_FILE_DEBUG_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_DEBUG_OUTPUT);
    }

    /* Create/Open a cross-reference output file if asked */

    if (AslGbl_CrossReferenceOutput)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_XREF);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_DEBUG_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        FlOpenFile (ASL_FILE_XREF_OUTPUT, Filename, "w+t");

        AslCompilerSignon (ASL_FILE_XREF_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_XREF_OUTPUT);
    }

    /* Create/Open a listing output file if asked */

    if (AslGbl_ListingFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_LISTING);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the listing file, text mode */

        FlOpenFile (ASL_FILE_LISTING_OUTPUT, Filename, "w+t");

        AslCompilerSignon (ASL_FILE_LISTING_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_LISTING_OUTPUT);
    }

    /* Create the preprocessor output temp file if preprocessor enabled */

    if (AslGbl_PreprocessFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_PREPROCESSOR);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_PREPROCESSOR_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        FlOpenFile (ASL_FILE_PREPROCESSOR, Filename, "w+t");
    }

    /*
     * Create the "user" preprocessor output file if -li flag set.
     * Note, this file contains no embedded #line directives.
     */
    if (AslGbl_PreprocessorOutputFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_PREPROC_USER);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_PREPROCESSOR_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        FlOpenFile (ASL_FILE_PREPROCESSOR_USER, Filename, "w+t");
    }

    /* All done for data table compiler */

    if (AslGbl_FileType == ASL_INPUT_TYPE_ASCII_DATA)
    {
        return (AE_OK);
    }

    /* Create/Open a combined source output file */

    Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_SOURCE);
    if (!Filename)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
            0, 0, 0, 0, NULL, NULL);
        return (AE_ERROR);
    }

    /*
     * Open the source output file, binary mode (so that LF does not get
     * expanded to CR/LF on some systems, messing up our seek
     * calculations.)
     */
    FlOpenFile (ASL_FILE_SOURCE_OUTPUT, Filename, "w+b");

/*
// TBD: TEMP
//    AslCompilerin = AslGbl_Files[ASL_FILE_SOURCE_OUTPUT].Handle;
*/
    /* Create/Open a assembly code source output file if asked */

    if (AslGbl_AsmOutputFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_ASM_SOURCE);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the assembly code source file, text mode */

        FlOpenFile (ASL_FILE_ASM_SOURCE_OUTPUT, Filename, "w+t");

        AslCompilerSignon (ASL_FILE_ASM_SOURCE_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_ASM_SOURCE_OUTPUT);
    }

    /* Create/Open a C code source output file if asked */

    if (AslGbl_C_OutputFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_C_SOURCE);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the C code source file, text mode */

        FlOpenFile (ASL_FILE_C_SOURCE_OUTPUT, Filename, "w+t");

        FlPrintFile (ASL_FILE_C_SOURCE_OUTPUT, "/*\n");
        AslCompilerSignon (ASL_FILE_C_SOURCE_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_C_SOURCE_OUTPUT);
    }

    /* Create/Open a C code source output file for the offset table if asked */

    if (AslGbl_C_OffsetTableFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_C_OFFSET);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the C code source file, text mode */

        FlOpenFile (ASL_FILE_C_OFFSET_OUTPUT, Filename, "w+t");

        FlPrintFile (ASL_FILE_C_OFFSET_OUTPUT, "/*\n");
        AslCompilerSignon (ASL_FILE_C_OFFSET_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_C_OFFSET_OUTPUT);
    }

    /* Create/Open a assembly include output file if asked */

    if (AslGbl_AsmIncludeOutputFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_ASM_INCLUDE);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the assembly include file, text mode */

        FlOpenFile (ASL_FILE_ASM_INCLUDE_OUTPUT, Filename, "w+t");

        AslCompilerSignon (ASL_FILE_ASM_INCLUDE_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_ASM_INCLUDE_OUTPUT);
    }

    /* Create/Open a C include output file if asked */

    if (AslGbl_C_IncludeOutputFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_C_INCLUDE);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the C include file, text mode */

        FlOpenFile (ASL_FILE_C_INCLUDE_OUTPUT, Filename, "w+t");

        FlPrintFile (ASL_FILE_C_INCLUDE_OUTPUT, "/*\n");
        AslCompilerSignon (ASL_FILE_C_INCLUDE_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_C_INCLUDE_OUTPUT);
    }

    /* Create a namespace output file if asked */

    if (AslGbl_NsOutputFlag)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_NAMESPACE);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the namespace file, text mode */

        FlOpenFile (ASL_FILE_NAMESPACE_OUTPUT, Filename, "w+t");

        AslCompilerSignon (ASL_FILE_NAMESPACE_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_NAMESPACE_OUTPUT);
    }

    /* Create a debug file for the converter */

    if (AcpiGbl_DebugAslConversion)
    {
        Filename = FlGenerateFilename (FilenamePrefix, FILE_SUFFIX_CONVERT_DEBUG);
        if (!Filename)
        {
            AslCommonError (ASL_ERROR, ASL_MSG_LISTING_FILENAME,
                0, 0, 0, 0, NULL, NULL);
            return (AE_ERROR);
        }

        /* Open the converter debug file, text mode */

        FlOpenFile (ASL_FILE_CONV_DEBUG_OUTPUT, Filename, "w+t");

        AslCompilerSignon (ASL_FILE_CONV_DEBUG_OUTPUT);
        AslCompilerFileHeader (ASL_FILE_CONV_DEBUG_OUTPUT);

        AcpiGbl_ConvDebugFile = AslGbl_Files[ASL_FILE_CONV_DEBUG_OUTPUT].Handle;
    }

    return (AE_OK);
}