#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {int /*<<< orphan*/  Filename; int /*<<< orphan*/  File; struct TYPE_9__* Parent; } ;
struct TYPE_7__ {char* CvFilename; } ;
struct TYPE_8__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_FILE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_FILE_AML_OUTPUT ; 
 int /*<<< orphan*/  ASL_MSG_OPEN ; 
 int /*<<< orphan*/  AcpiGbl_CurrentFilename ; 
 int /*<<< orphan*/  AcpiGbl_FileTreeRoot ; 
 int /*<<< orphan*/  AcpiOsRedirectOutput (int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiUtStricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslAbort () ; 
 int /*<<< orphan*/  AslCommonError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  CvDbgPrint (char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* CvFilenameExists (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CvPrintInclude (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlDeleteFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
CvSwitchFiles(
    UINT32                  Level,
    ACPI_PARSE_OBJECT       *Op)
{
    char                    *Filename = Op->Common.CvFilename;
    ACPI_FILE_NODE          *FNode;
    ACPI_FILE_NODE          *Current;


    CvDbgPrint ("Switching from %s to %s\n", AcpiGbl_CurrentFilename,
        Filename);
    FNode = CvFilenameExists (Filename, AcpiGbl_FileTreeRoot);
    if (!FNode)
    {
        /*
         * At this point, each Filename should exist in AcpiGbl_FileTreeRoot
         * if it does not exist, then abort.
         */
        FlDeleteFile (ASL_FILE_AML_OUTPUT);
        sprintf (AslGbl_MsgBuffer, "\"Cannot find %s\" - %s",
            Filename, strerror (errno));
        AslCommonError (ASL_ERROR, ASL_MSG_OPEN, 0, 0, 0, 0,
            NULL, AslGbl_MsgBuffer);
        AslAbort ();
    }

    Current = FNode;

    /*
     * If the previous file is a descendent of the current file,
     * make sure that Include statements from the current file
     * to the previous have been emitted.
     */
    while (Current &&
           Current->Parent &&
           AcpiUtStricmp (Current->Filename, AcpiGbl_CurrentFilename))
    {
        CvPrintInclude (Current, Level);
        Current = Current->Parent;
    }

    if (FNode)
    {
        /* Redirect output to Op->Common.CvFilename */

        AcpiOsRedirectOutput (FNode->File);
        AcpiGbl_CurrentFilename = FNode->Filename;
    }
}