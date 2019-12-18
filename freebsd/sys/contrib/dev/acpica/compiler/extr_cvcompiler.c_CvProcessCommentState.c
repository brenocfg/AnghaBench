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
struct TYPE_2__ {void* CommentType; int /*<<< orphan*/ * ParsingParenBraceNode; scalar_t__ SpacesBefore; } ;

/* Variables and functions */
 void* ASLCOMMENT_INLINE ; 
 void* ASL_COMMENT_CLOSE_BRACE ; 
 void* ASL_COMMENT_CLOSE_PAREN ; 
 void* ASL_COMMENT_OPEN_PAREN ; 
 void* ASL_COMMENT_STANDARD ; 
 TYPE_1__ AslGbl_CommentState ; 
 int /*<<< orphan*/  CvDbgPrint (char*) ; 

void
CvProcessCommentState (
    char                    Input)
{

    if (Input != ' ')
    {
        AslGbl_CommentState.SpacesBefore = 0;
    }

    switch (Input)
    {
    case '\n':

        AslGbl_CommentState.CommentType = ASL_COMMENT_STANDARD;
        break;

    case ' ':

        /* Keep the CommentType the same */

        AslGbl_CommentState.SpacesBefore++;
        break;

    case '(':

        AslGbl_CommentState.CommentType = ASL_COMMENT_OPEN_PAREN;
        break;

    case ')':

        AslGbl_CommentState.CommentType = ASL_COMMENT_CLOSE_PAREN;
        break;

    case '{':

        AslGbl_CommentState.CommentType = ASL_COMMENT_STANDARD;
        AslGbl_CommentState.ParsingParenBraceNode = NULL;
        CvDbgPrint ("End Parsing paren/Brace node!\n");
        break;

    case '}':

        AslGbl_CommentState.CommentType = ASL_COMMENT_CLOSE_BRACE;
        break;

    case ',':

        AslGbl_CommentState.CommentType = ASLCOMMENT_INLINE;
        break;

    default:

        AslGbl_CommentState.CommentType = ASLCOMMENT_INLINE;
        break;
    }
}