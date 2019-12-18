#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_8__ {char* Comment; struct TYPE_8__* Next; } ;
struct TYPE_6__ {scalar_t__ ParseOpcode; char* CloseBraceComment; TYPE_3__* CommentList; int /*<<< orphan*/  Filename; } ;
struct TYPE_7__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_COMMENT_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiGbl_CaptureComments ; 
 int /*<<< orphan*/  CgWriteOneAmlComment (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CvDbgPrint (char*,...) ; 
 int /*<<< orphan*/  END_DEFBLK_COMMENT ; 
 int /*<<< orphan*/  FILENAME_COMMENT ; 
 char* FILE_SUFFIX_DISASSEMBLY ; 
 scalar_t__ PARSEOP_DEFINITION_BLOCK ; 
 int /*<<< orphan*/  STD_DEFBLK_COMMENT ; 
 char* UtLocalCacheCalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

void
CgWriteAmlDefBlockComment(
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   CommentOption;
    ACPI_COMMENT_NODE       *Current;
    char                    *NewFilename;
    char                    *Position;
    char                    *DirectoryPosition;


    if (!AcpiGbl_CaptureComments ||
        (Op->Asl.ParseOpcode != PARSEOP_DEFINITION_BLOCK))
    {
        return;
    }

    CvDbgPrint ("Printing comments for a definition block..\n");

    /* First, print the file name comment after changing .asl to .dsl */

    NewFilename = UtLocalCacheCalloc (strlen (Op->Asl.Filename));
    strcpy (NewFilename, Op->Asl.Filename);
    DirectoryPosition = strrchr (NewFilename, '/');
    Position = strrchr (NewFilename, '.');

    if (Position && (Position > DirectoryPosition))
    {
        /* Tack on the new suffix */

        Position++;
        *Position = 0;
        strcat (Position, FILE_SUFFIX_DISASSEMBLY);
    }
    else
    {
        /* No dot, add one and then the suffix */

        strcat (NewFilename, ".");
        strcat (NewFilename, FILE_SUFFIX_DISASSEMBLY);
    }

    CommentOption = FILENAME_COMMENT;
    CgWriteOneAmlComment(Op, NewFilename, CommentOption);

    Current = Op->Asl.CommentList;
    CommentOption = STD_DEFBLK_COMMENT;

    while (Current)
    {
        CgWriteOneAmlComment(Op, Current->Comment, CommentOption);
        CvDbgPrint ("Printing comment: %s\n", Current->Comment);
        Current = Current->Next;
    }

    Op->Asl.CommentList = NULL;

    /* Print any Inline comments associated with this node */

    if (Op->Asl.CloseBraceComment)
    {
        CommentOption = END_DEFBLK_COMMENT;
        CgWriteOneAmlComment(Op, Op->Asl.CloseBraceComment, CommentOption);
        Op->Asl.CloseBraceComment = NULL;
    }
}