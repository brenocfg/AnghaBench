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
typedef  size_t UINT32 ;
struct TYPE_2__ {scalar_t__ Handle; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 size_t ASL_FILE_AML_OUTPUT ; 
 size_t ASL_FILE_INPUT ; 
 size_t ASL_FILE_PREPROCESSOR ; 
 size_t ASL_FILE_SOURCE_OUTPUT ; 
 size_t ASL_MAX_FILE_TYPE ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_KeepPreprocessorTempFile ; 
 scalar_t__ AslGbl_PreprocessFlag ; 
 int /*<<< orphan*/  AslGbl_SourceOutputFlag ; 
 int /*<<< orphan*/  FlCloseFile (size_t) ; 
 int /*<<< orphan*/  FlDeleteFile (size_t) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 

__attribute__((used)) static void
CmFinishFiles(
    BOOLEAN                 DeleteAmlFile)
{
    UINT32                  i;


    /*
     * Take care with the preprocessor file (.pre), it might be the same
     * as the "input" file, depending on where the compiler has terminated
     * or aborted. Prevent attempt to close the same file twice in
     * loop below.
     */
    if (AslGbl_Files[ASL_FILE_PREPROCESSOR].Handle ==
        AslGbl_Files[ASL_FILE_INPUT].Handle)
    {
        AslGbl_Files[ASL_FILE_PREPROCESSOR].Handle = NULL;
    }

    /* Close the standard I/O files */

    for (i = ASL_FILE_INPUT; i < ASL_MAX_FILE_TYPE; i++)
    {
        /*
         * Some files such as debug output files could be pointing to
         * stderr or stdout. Leave these alone.
         */
        if (AslGbl_Files[i].Handle != stderr &&
            AslGbl_Files[i].Handle != stdout)
        {
            FlCloseFile (i);
        }
    }

    /* Delete AML file if there are errors */

    if (DeleteAmlFile)
    {
        FlDeleteFile (ASL_FILE_AML_OUTPUT);
    }

    /* Delete the preprocessor temp file unless full debug was specified */

    if (AslGbl_PreprocessFlag && !AslGbl_KeepPreprocessorTempFile)
    {
        FlDeleteFile (ASL_FILE_PREPROCESSOR);
    }

    /*
     * Delete intermediate ("combined") source file (if -ls flag not set)
     * This file is created during normal ASL/AML compiles. It is not
     * created by the data table compiler.
     *
     * If the -ls flag is set, then the .SRC file should not be deleted.
     * In this case, Gbl_SourceOutputFlag is set to TRUE.
     *
     * Note: Handles are cleared by FlCloseFile above, so we look at the
     * filename instead, to determine if the .SRC file was actually
     * created.
     */
    if (!AslGbl_SourceOutputFlag)
    {
        FlDeleteFile (ASL_FILE_SOURCE_OUTPUT);
    }
}