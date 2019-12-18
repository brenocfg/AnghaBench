#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* FileEnd; char* Filename; char* FileStart; int /*<<< orphan*/  File; int /*<<< orphan*/  IncludeWritten; struct TYPE_6__* Parent; struct TYPE_6__* Next; } ;
typedef  TYPE_1__ ACPI_FILE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_FILE_AML_OUTPUT ; 
 int /*<<< orphan*/  ASL_MSG_OPEN ; 
 int /*<<< orphan*/  AcpiGbl_FileCache ; 
 TYPE_1__* AcpiGbl_FileTreeRoot ; 
 int /*<<< orphan*/  AcpiGbl_RootFilename ; 
 TYPE_1__* AcpiOsAcquireObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtStricmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslAbort () ; 
 int /*<<< orphan*/  AslCommonError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 TYPE_1__* CvFilenameExists (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlDeleteFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CvAddToFileTree (
    char                    *Filename,
    char                    *PreviousFilename)
{
    ACPI_FILE_NODE          *Node;


    if (!AcpiUtStricmp(Filename, AcpiGbl_RootFilename) &&
        PreviousFilename)
    {
        Node = CvFilenameExists (PreviousFilename, AcpiGbl_FileTreeRoot);
        if (Node)
        {
            /*
             * Set the end point of the PreviousFilename to the address
             * of Filename.
             */
            Node->FileEnd = Filename;
        }
    }
    else if (!AcpiUtStricmp(Filename, AcpiGbl_RootFilename) &&
             !PreviousFilename)
    {
        return;
    }

    Node = CvFilenameExists (Filename, AcpiGbl_FileTreeRoot);
    if (Node && PreviousFilename)
    {
        /*
         * Update the end of the previous file and all of their parents'
         * ending addresses. This is done to ensure that parent file
         * ranges extend to the end of their childrens' files.
         */
        Node = CvFilenameExists (PreviousFilename, AcpiGbl_FileTreeRoot);
        if (Node && (Node->FileEnd < Filename))
        {
            Node->FileEnd = Filename;
            Node = Node->Parent;
            while (Node)
            {
                if (Node->FileEnd < Filename)
                {
                    Node->FileEnd = Filename;
                }

                Node = Node->Parent;
            }
        }
    }
    else
    {
        Node = AcpiGbl_FileTreeRoot;
        AcpiGbl_FileTreeRoot = AcpiOsAcquireObject (AcpiGbl_FileCache);

        AcpiGbl_FileTreeRoot->Next = Node;
        AcpiGbl_FileTreeRoot->Parent = NULL;
        AcpiGbl_FileTreeRoot->Filename = Filename;
        AcpiGbl_FileTreeRoot->FileStart = Filename;
        AcpiGbl_FileTreeRoot->IncludeWritten = FALSE;
        AcpiGbl_FileTreeRoot->File = fopen(Filename, "w+");

        /*
         * If we can't open the file, we need to abort here before we
         * accidentally write to a NULL file.
         */
        if (!AcpiGbl_FileTreeRoot->File)
        {
            /* delete the .xxx file */

            FlDeleteFile (ASL_FILE_AML_OUTPUT);
            sprintf (AslGbl_MsgBuffer, "\"%s\" - %s", Filename, strerror (errno));
            AslCommonError (ASL_ERROR, ASL_MSG_OPEN, 0, 0, 0, 0,
                NULL, AslGbl_MsgBuffer);
            AslAbort ();
        }
    }
}