#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_3__ {int SpacesBefore; int CommentType; scalar_t__ CaptureComments; } ;
typedef  TYPE_1__ ASL_COMMENT_STATE ;

/* Variables and functions */
 scalar_t__ AcpiGbl_CaptureComments ; 
 char* AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  CvDbgPrint (char*) ; 
 int /*<<< orphan*/  CvPlaceComment (int,char*) ; 
 char* UtLocalCacheCalloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

void
CvProcessCommentType2 (
    ASL_COMMENT_STATE       CurrentState,
    char                    *StringBuffer)
{
    UINT32                  i;
    char                    *CommentString;
    char                    *FinalCommentString;


    if (AcpiGbl_CaptureComments && CurrentState.CaptureComments)
    {
        *StringBuffer = 0; /* null terminate */
        CvDbgPrint ("Single-line comment\n");
        CommentString = UtLocalCacheCalloc (strlen (AslGbl_MsgBuffer) + 1);
        strcpy (CommentString, AslGbl_MsgBuffer);

        /* If this comment lies on the same line as the latest parse op,
         * assign it to that op's CommentAfter field. Saving in this field
         * will allow us to support comments that come after code on the
         * same line as the code itself. For example,
         * Name(A,"") //comment
         *
         * will be retained rather than transformed into
         *
         * Name(A,"")
         * //comment
         *
         * For this case, we only need to add one comment since
         *
         * Name(A,"") //comment1 //comment2 ... more comments here.
         *
         * would be lexically analyzed as a single comment.
         *
         * Create a new string with the appropriate spaces. Since we need
         * to account for the proper spacing, the actual comment,
         * extra 2 spaces so that this comment can be converted to the "/ *"
         * style and the null terminator, the string would look something
         * like:
         *
         * [ (spaces) (comment)  ( * /) ('\0') ]
         *
         */
        FinalCommentString = UtLocalCacheCalloc (CurrentState.SpacesBefore +
            strlen (CommentString) + 3 + 1);

        for (i = 0; (CurrentState.CommentType != 1) &&
            (i < CurrentState.SpacesBefore); i++)
        {
            FinalCommentString[i] = ' ';
        }

        strcat (FinalCommentString, CommentString);

        /* convert to a "/ *" style comment  */

        strcat (FinalCommentString, " */");
        FinalCommentString [CurrentState.SpacesBefore +
            strlen (CommentString) + 3] = 0;

        /* get rid of the carriage return */

        if (FinalCommentString[strlen (FinalCommentString) - 1] == 0x0D)
        {
            FinalCommentString[strlen(FinalCommentString) - 1] = 0;
        }

        CvPlaceComment (CurrentState.CommentType, FinalCommentString);
    }
}