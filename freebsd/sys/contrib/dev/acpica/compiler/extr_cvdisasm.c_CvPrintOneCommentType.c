#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {char* InlineComment; char* EndNodeComment; char* NameComment; char* CloseBraceComment; int /*<<< orphan*/ * EndBlkComment; int /*<<< orphan*/ * CommentList; } ;
struct TYPE_5__ {TYPE_1__ Common; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  AMLCOMMENT_INLINE 133 
#define  AML_COMMENT_CLOSE_BRACE 132 
#define  AML_COMMENT_ENDBLK 131 
#define  AML_COMMENT_END_NODE 130 
#define  AML_COMMENT_STANDARD 129 
#define  AML_NAMECOMMENT 128 
 int /*<<< orphan*/  AcpiDmIndent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  CvListIsSingleton (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CvPrintOneCommentList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

void
CvPrintOneCommentType (
    ACPI_PARSE_OBJECT       *Op,
    UINT8                   CommentType,
    char*                   EndStr,
    UINT32                  Level)
{
    BOOLEAN                 CommentExists = FALSE;
    char                    **CommentToPrint = NULL;


    switch (CommentType)
    {
    case AML_COMMENT_STANDARD:

        if (CvListIsSingleton (Op->Common.CommentList))
        {
            CvPrintOneCommentList (Op->Common.CommentList, Level);
            AcpiOsPrintf ("\n");
        }
        else
        {
            CvPrintOneCommentList (Op->Common.CommentList, Level);
        }

        Op->Common.CommentList = NULL;
        return;

    case AML_COMMENT_ENDBLK:

        if (Op->Common.EndBlkComment)
        {
            CvPrintOneCommentList (Op->Common.EndBlkComment, Level);
            Op->Common.EndBlkComment = NULL;
            AcpiDmIndent(Level);
        }
        return;

    case AMLCOMMENT_INLINE:

        CommentToPrint = &Op->Common.InlineComment;
        break;

    case AML_COMMENT_END_NODE:

        CommentToPrint = &Op->Common.EndNodeComment;
        break;

    case AML_NAMECOMMENT:

        CommentToPrint = &Op->Common.NameComment;
        break;

    case AML_COMMENT_CLOSE_BRACE:

        CommentToPrint = &Op->Common.CloseBraceComment;
        break;

    default:
        return;
    }

    if (*CommentToPrint)
    {
        CommentExists = TRUE;
        AcpiOsPrintf ("%s", *CommentToPrint);
        *CommentToPrint = NULL;
    }

    if (CommentExists && EndStr)
    {
        AcpiOsPrintf ("%s", EndStr);
    }
}