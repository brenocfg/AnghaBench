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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
struct TYPE_6__ {TYPE_2__* ParsingParenBraceNode; TYPE_2__* LatestParseOp; } ;
struct TYPE_4__ {char* CloseBraceComment; void* EndNodeComment; void* InlineComment; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  ASLCOMMENT_INLINE 132 
#define  ASL_COMMENT_CLOSE_BRACE 131 
#define  ASL_COMMENT_CLOSE_PAREN 130 
#define  ASL_COMMENT_OPEN_PAREN 129 
#define  ASL_COMMENT_STANDARD 128 
 TYPE_3__ AslGbl_CommentState ; 
 void* AslGbl_InlineCommentBuffer ; 
 int /*<<< orphan*/  CvAddToCommentList (char*) ; 
 void* CvAppendInlineComment (void*,char*) ; 
 int /*<<< orphan*/  CvDbgPrint (char*,char*,int) ; 

void
CvPlaceComment(
    UINT8                   Type,
    char                    *CommentString)
{
    ACPI_PARSE_OBJECT       *LatestParseNode;
    ACPI_PARSE_OBJECT       *ParenBraceNode;


    LatestParseNode = AslGbl_CommentState.LatestParseOp;
    ParenBraceNode  = AslGbl_CommentState.ParsingParenBraceNode;
    CvDbgPrint ("Placing comment %s for type %d\n", CommentString, Type);

    switch (Type)
    {
    case ASL_COMMENT_STANDARD:

        CvAddToCommentList (CommentString);
        break;

    case ASLCOMMENT_INLINE:

        LatestParseNode->Asl.InlineComment =
            CvAppendInlineComment (LatestParseNode->Asl.InlineComment,
            CommentString);
        break;

    case ASL_COMMENT_OPEN_PAREN:

        AslGbl_InlineCommentBuffer =
            CvAppendInlineComment(AslGbl_InlineCommentBuffer,
            CommentString);
        break;

    case ASL_COMMENT_CLOSE_PAREN:

        if (ParenBraceNode)
        {
            ParenBraceNode->Asl.EndNodeComment =
                CvAppendInlineComment (ParenBraceNode->Asl.EndNodeComment,
                CommentString);
        }
        else
        {
            LatestParseNode->Asl.EndNodeComment =
                CvAppendInlineComment (LatestParseNode->Asl.EndNodeComment,
                CommentString);
        }
        break;

    case ASL_COMMENT_CLOSE_BRACE:

        LatestParseNode->Asl.CloseBraceComment = CommentString;
        break;

    default:

        break;
    }
}