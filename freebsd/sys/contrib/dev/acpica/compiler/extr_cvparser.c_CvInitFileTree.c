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
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
struct TYPE_6__ {char* FileStart; char* FileEnd; char* Filename; int /*<<< orphan*/  IncludeWritten; int /*<<< orphan*/  File; int /*<<< orphan*/ * Parent; int /*<<< orphan*/ * Next; } ;
struct TYPE_5__ {int Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 scalar_t__ AML_COMMENT_OP ; 
 int /*<<< orphan*/  AcpiGbl_CaptureComments ; 
 char* AcpiGbl_CurrentFilename ; 
 int /*<<< orphan*/  AcpiGbl_FileCache ; 
 TYPE_3__* AcpiGbl_FileTreeRoot ; 
 int /*<<< orphan*/  AcpiGbl_OutputFile ; 
 char* AcpiGbl_RootFilename ; 
 TYPE_3__* AcpiOsAcquireObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CvAddToFileTree (char*,char*) ; 
 int /*<<< orphan*/  CvDbgPrint (char*,...) ; 
 scalar_t__ CvIsFilename (char*) ; 
 int /*<<< orphan*/  CvSetFileParent (char*,char*) ; 
 scalar_t__ FILENAME_COMMENT ; 
 scalar_t__ PARENTFILENAME_COMMENT ; 
 int /*<<< orphan*/  TRUE ; 

void
CvInitFileTree (
    ACPI_TABLE_HEADER       *Table,
    UINT8                   *AmlStart,
    UINT32                  AmlLength)
{
    UINT8                   *TreeAml;
    UINT8                   *FileEnd;
    char                    *Filename = NULL;
    char                    *PreviousFilename = NULL;
    char                    *ParentFilename = NULL;
    char                    *ChildFilename = NULL;


    if (!AcpiGbl_CaptureComments)
    {
        return;
    }

    CvDbgPrint ("AmlLength: %x\n", AmlLength);
    CvDbgPrint ("AmlStart:  %p\n", AmlStart);
    CvDbgPrint ("AmlEnd?:   %p\n", AmlStart+AmlLength);

    AcpiGbl_FileTreeRoot = AcpiOsAcquireObject (AcpiGbl_FileCache);

    AcpiGbl_FileTreeRoot->FileStart = (char *)(AmlStart);
    AcpiGbl_FileTreeRoot->FileEnd = (char *)(AmlStart + Table->Length);
    AcpiGbl_FileTreeRoot->Next = NULL;
    AcpiGbl_FileTreeRoot->Parent = NULL;
    AcpiGbl_FileTreeRoot->Filename = (char *)(AmlStart+2);

    /* Set the root file to the current open file */

    AcpiGbl_FileTreeRoot->File = AcpiGbl_OutputFile;

    /*
     * Set this to true because we don't need to output
     * an include statement for the topmost file
     */
    AcpiGbl_FileTreeRoot->IncludeWritten = TRUE;
    Filename = NULL;
    AcpiGbl_CurrentFilename = (char *)(AmlStart+2);
    AcpiGbl_RootFilename    = (char *)(AmlStart+2);

    TreeAml = AmlStart;
    FileEnd = AmlStart + AmlLength;

    while (TreeAml <= FileEnd)
    {
        /*
         * Make sure that this filename contains all printable characters
         * and a .dsl extension at the end. If not, then it must be some
         * raw data that doesn't outline a filename.
         */
        if ((*TreeAml == AML_COMMENT_OP) &&
            (*(TreeAml +1) == FILENAME_COMMENT) &&
            (CvIsFilename ((char *)(TreeAml +2))))
        {
            CvDbgPrint ("A9 and a 08 file\n");
            PreviousFilename = Filename;
            Filename = (char *) (TreeAml +2);

            CvAddToFileTree (Filename, PreviousFilename);
            ChildFilename = Filename;
            CvDbgPrint ("%s\n", Filename);
        }
        else if ((*TreeAml == AML_COMMENT_OP) &&
            (*(TreeAml +1) == PARENTFILENAME_COMMENT) &&
            (CvIsFilename ((char *)(TreeAml +2))))
        {
            CvDbgPrint ("A9 and a 09 file\n");
            ParentFilename = (char *)(TreeAml +2);
            CvSetFileParent (ChildFilename, ParentFilename);
            CvDbgPrint ("%s\n", ParentFilename);
        }

        ++TreeAml;
    }
}