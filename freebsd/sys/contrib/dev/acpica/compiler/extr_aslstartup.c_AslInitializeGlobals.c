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
struct TYPE_2__ {int CommentType; int /*<<< orphan*/  CaptureComments; int /*<<< orphan*/ * ParsingParenBraceNode; int /*<<< orphan*/ * LatestParseOp; scalar_t__ SpacesBefore; } ;

/* Variables and functions */
 size_t ASL_NUM_REPORT_LEVELS ; 
 scalar_t__ AcpiGbl_CaptureComments ; 
 TYPE_1__ AslGbl_CommentState ; 
 scalar_t__ AslGbl_CurrentColumn ; 
 int /*<<< orphan*/  AslGbl_CurrentLineBuffer ; 
 int AslGbl_CurrentLineNumber ; 
 scalar_t__ AslGbl_CurrentLineOffset ; 
 int /*<<< orphan*/ * AslGbl_ErrorLog ; 
 scalar_t__* AslGbl_ExceptionCount ; 
 scalar_t__ AslGbl_FileType ; 
 scalar_t__ AslGbl_InputByteCount ; 
 scalar_t__ AslGbl_InputFieldCount ; 
 int /*<<< orphan*/  AslGbl_LineBufPtr ; 
 int AslGbl_LogicalLineNumber ; 
 int /*<<< orphan*/ * AslGbl_NextError ; 
 scalar_t__ AslGbl_NextEvent ; 
 scalar_t__ AslGbl_NsLookupCount ; 
 int /*<<< orphan*/ * AslGbl_Signature ; 
 scalar_t__ AslGbl_SyntaxError ; 
 scalar_t__ AslGbl_TotalAllocated ; 
 scalar_t__ AslGbl_TotalAllocations ; 
 scalar_t__ AslGbl_TotalExecutableOpcodes ; 
 scalar_t__ AslGbl_TotalFolds ; 
 scalar_t__ AslGbl_TotalKeywords ; 
 scalar_t__ AslGbl_TotalMethods ; 
 scalar_t__ AslGbl_TotalNamedObjects ; 
 scalar_t__ AslGbl_TotalParseNodes ; 
 int /*<<< orphan*/  TRUE ; 

void
AslInitializeGlobals (
    void)
{
    UINT32                  i;


    /* Init compiler globals */

    AslGbl_SyntaxError = 0;
    AslGbl_CurrentColumn = 0;
    AslGbl_CurrentLineNumber = 1;
    AslGbl_LogicalLineNumber = 1;
    AslGbl_CurrentLineOffset = 0;
    AslGbl_InputFieldCount = 0;
    AslGbl_InputByteCount = 0;
    AslGbl_NsLookupCount = 0;
    AslGbl_LineBufPtr = AslGbl_CurrentLineBuffer;

    AslGbl_ErrorLog = NULL;
    AslGbl_NextError = NULL;
    AslGbl_Signature = NULL;
    AslGbl_FileType = 0;

    AslGbl_TotalExecutableOpcodes = 0;
    AslGbl_TotalNamedObjects = 0;
    AslGbl_TotalKeywords = 0;
    AslGbl_TotalParseNodes = 0;
    AslGbl_TotalMethods = 0;
    AslGbl_TotalAllocations = 0;
    AslGbl_TotalAllocated = 0;
    AslGbl_TotalFolds = 0;

    AslGbl_NextEvent = 0;
    for (i = 0; i < ASL_NUM_REPORT_LEVELS; i++)
    {
        AslGbl_ExceptionCount[i] = 0;
    }

    if (AcpiGbl_CaptureComments)
    {
        AslGbl_CommentState.SpacesBefore          = 0;
        AslGbl_CommentState.CommentType           = 1;
        AslGbl_CommentState.LatestParseOp         = NULL;
        AslGbl_CommentState.ParsingParenBraceNode = NULL;
        AslGbl_CommentState.CaptureComments       = TRUE;
    }
}