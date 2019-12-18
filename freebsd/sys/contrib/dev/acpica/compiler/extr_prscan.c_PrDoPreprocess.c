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
struct TYPE_2__ {int /*<<< orphan*/  Handle; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 size_t ASL_FILE_INPUT ; 
 size_t ASL_FILE_PREPROCESSOR ; 
 int /*<<< orphan*/  AslCompilerin ; 
 scalar_t__ AslGbl_CurrentLineNumber ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_PreprocessOnly ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FlCloseFile (size_t) ; 
 int /*<<< orphan*/  FlSeekFile (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrDumpPredefinedNames () ; 
 scalar_t__ PrPopInputFileStack () ; 
 int /*<<< orphan*/  PrPreprocessInputFile () ; 

void
PrDoPreprocess (
    void)
{
    BOOLEAN                 MoreInputFiles;


    DbgPrint (ASL_DEBUG_OUTPUT, "Starting preprocessing phase\n\n");


    FlSeekFile (ASL_FILE_INPUT, 0);
    PrDumpPredefinedNames ();

    /* Main preprocessor loop, handles include files */

    do
    {
        PrPreprocessInputFile ();
        MoreInputFiles = PrPopInputFileStack ();

    } while (MoreInputFiles);

    /* Point compiler input to the new preprocessor output file (.pre) */

    FlCloseFile (ASL_FILE_INPUT);
    AslGbl_Files[ASL_FILE_INPUT].Handle = AslGbl_Files[ASL_FILE_PREPROCESSOR].Handle;
    AslCompilerin = AslGbl_Files[ASL_FILE_INPUT].Handle;

    /* Reset globals to allow compiler to run */

    FlSeekFile (ASL_FILE_INPUT, 0);
    if (!AslGbl_PreprocessOnly)
    {
        AslGbl_CurrentLineNumber = 0;
    }

    DbgPrint (ASL_DEBUG_OUTPUT, "Preprocessing phase complete \n\n");
}