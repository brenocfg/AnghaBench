#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_9__ {scalar_t__ StartTime; scalar_t__ EndTime; } ;
struct TYPE_8__ {scalar_t__ Handle; } ;
struct TYPE_7__ {struct TYPE_7__* Next; TYPE_1__* Files; scalar_t__ ParserErrorDetected; } ;
struct TYPE_6__ {int /*<<< orphan*/  Filename; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ASL_GLOBAL_FILE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 size_t ASL_ERROR ; 
 size_t ASL_FILE_AML_OUTPUT ; 
 size_t ASL_FILE_INPUT ; 
 int /*<<< orphan*/  ASL_FILE_STDERR ; 
 int /*<<< orphan*/  ASL_FILE_STDOUT ; 
 int ASL_MAX_ERROR_COUNT ; 
 int /*<<< orphan*/  AePrintErrorLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslCheckForErrorExit () ; 
 scalar_t__ AslGbl_CompileTimesFlag ; 
 scalar_t__ AslGbl_DebugFlag ; 
 int /*<<< orphan*/  AslGbl_DoAslConversion ; 
 TYPE_5__* AslGbl_Events ; 
 int* AslGbl_ExceptionCount ; 
 TYPE_4__* AslGbl_Files ; 
 TYPE_2__* AslGbl_FilesList ; 
 int /*<<< orphan*/  AslGbl_IgnoreErrors ; 
 size_t AslGbl_NamespaceEvent ; 
 int AslGbl_NsLookupCount ; 
 scalar_t__ AslGbl_ParserErrorDetected ; 
 scalar_t__ AslGbl_PreprocessOnly ; 
 int AslGbl_TotalAllocated ; 
 int AslGbl_TotalAllocations ; 
 int AslGbl_TotalFolds ; 
 int AslGbl_TotalMethods ; 
 int AslGbl_TotalNamedObjects ; 
 int AslGbl_TotalParseNodes ; 
 int /*<<< orphan*/  CmDumpAllEvents () ; 
 int /*<<< orphan*/  CmFinishFiles (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
#define  FILE_NOT_FOUND 130 
 int FlSwitchFileSet (int /*<<< orphan*/ ) ; 
#define  SWITCH_TO_DIFFERENT_FILE 129 
#define  SWITCH_TO_SAME_FILE 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UtDeleteLocalCaches () ; 
 int /*<<< orphan*/  UtDisplaySummary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
CmCleanupAndExit (
    void)
{
    int                     Status = 0;
    BOOLEAN                 DeleteAmlFile = FALSE;
    ASL_GLOBAL_FILE_NODE    *CurrentFileNode = AslGbl_FilesList;


    /* Check if any errors occurred during compile */

    (void) AslCheckForErrorExit ();

    AePrintErrorLog (ASL_FILE_STDERR);
    if (AslGbl_DebugFlag)
    {
        /* Print error summary to stdout also */

        AePrintErrorLog (ASL_FILE_STDOUT);
    }

    /* Emit compile times if enabled */

    CmDumpAllEvents ();

    if (AslGbl_CompileTimesFlag)
    {
        printf ("\nMiscellaneous compile statistics\n\n");
        printf ("%11u : %s\n", AslGbl_TotalParseNodes, "Parse nodes");
        printf ("%11u : %s\n", AslGbl_NsLookupCount, "Namespace searches");
        printf ("%11u : %s\n", AslGbl_TotalNamedObjects, "Named objects");
        printf ("%11u : %s\n", AslGbl_TotalMethods, "Control methods");
        printf ("%11u : %s\n", AslGbl_TotalAllocations, "Memory Allocations");
        printf ("%11u : %s\n", AslGbl_TotalAllocated, "Total allocated memory");
        printf ("%11u : %s\n", AslGbl_TotalFolds, "Constant subtrees folded");
        printf ("\n");
    }

    if (AslGbl_NsLookupCount)
    {
        DbgPrint (ASL_DEBUG_OUTPUT,
            "\n\nMiscellaneous compile statistics\n\n");

        DbgPrint (ASL_DEBUG_OUTPUT,
            "%32s : %u\n", "Total Namespace searches",
            AslGbl_NsLookupCount);

        DbgPrint (ASL_DEBUG_OUTPUT,
            "%32s : %u usec\n", "Time per search", ((UINT32)
            (AslGbl_Events[AslGbl_NamespaceEvent].EndTime -
                AslGbl_Events[AslGbl_NamespaceEvent].StartTime) / 10) /
                AslGbl_NsLookupCount);
    }

    if (AslGbl_ExceptionCount[ASL_ERROR] > ASL_MAX_ERROR_COUNT)
    {
        printf ("\nMaximum error count (%d) exceeded\n",
            ASL_MAX_ERROR_COUNT);
    }

    UtDisplaySummary (ASL_FILE_STDOUT);

    /*
     * Delete the AML file if there are errors and the force AML output option
     * (-f) has not been used.
     *
     * Return -1 as a status of the compiler if no AML files are generated. If
     * the AML file is generated in the presence of errors, return 0. In the
     * latter case, the errors were ignored by the user so the compilation is
     * considered successful.
     */
    if (AslGbl_ParserErrorDetected || AslGbl_PreprocessOnly ||
        ((AslGbl_ExceptionCount[ASL_ERROR] > 0) &&
        (!AslGbl_IgnoreErrors) &&
        AslGbl_Files[ASL_FILE_AML_OUTPUT].Handle))
    {
        DeleteAmlFile = TRUE;
        Status = -1;
    }

    /* Close all open files */

    while (CurrentFileNode)
    {
        /*
         * Set the program return status based on file errors. If there are any
         * errors and during compilation, the command is not considered
         * successful.
         */
        if (Status != -1 && !AslGbl_IgnoreErrors &&
            CurrentFileNode->ParserErrorDetected)
        {
            Status = -1;
        }

        switch  (FlSwitchFileSet (CurrentFileNode->Files[ASL_FILE_INPUT].Filename))
        {
            case SWITCH_TO_SAME_FILE:
            case SWITCH_TO_DIFFERENT_FILE:

                CmFinishFiles (DeleteAmlFile);
                CurrentFileNode = CurrentFileNode->Next;
                break;

            case FILE_NOT_FOUND:
            default:

                CurrentFileNode = NULL;
                break;
        }
    }

    /* Final cleanup after compiling one file */

    if (!AslGbl_DoAslConversion)
    {
        UtDeleteLocalCaches ();
    }

    return (Status);
}