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
typedef  int UINT64 ;
struct TYPE_3__ {int SpacesBefore; scalar_t__ CommentType; scalar_t__ CaptureComments; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_1__ ASL_COMMENT_STATE ;

/* Variables and functions */
 scalar_t__ ASL_COMMENT_STANDARD ; 
 scalar_t__ AcpiGbl_CaptureComments ; 
 char* AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  CvAddToCommentList (char*) ; 
 int /*<<< orphan*/  CvDbgPrint (char*,...) ; 
 int /*<<< orphan*/  CvPlaceComment (scalar_t__,char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 char* UtLocalCacheCalloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 

void
CvProcessComment (
    ASL_COMMENT_STATE       CurrentState,
    char                    *StringBuffer,
    int                     c1)
{
    UINT64                  i;
    char                    *LineToken;
    char                    *FinalLineToken;
    BOOLEAN                 CharStart;
    char                    *CommentString;
    char                    *FinalCommentString;


    if (AcpiGbl_CaptureComments && CurrentState.CaptureComments)
    {
        *StringBuffer = (char) c1;
        ++StringBuffer;
        *StringBuffer = 0;

        CvDbgPrint ("Multi-line comment\n");
        CommentString = UtLocalCacheCalloc (strlen (AslGbl_MsgBuffer) + 1);
        strcpy (CommentString, AslGbl_MsgBuffer);

        CvDbgPrint ("CommentString: %s\n", CommentString);

        /*
         * Determine whether if this comment spans multiple lines. If so,
         * break apart the comment by storing each line in a different node
         * within the comment list. This allows the disassembler to
         * properly indent a multi-line comment.
         */
        LineToken = strtok (CommentString, "\n");

        if (LineToken)
        {
            FinalLineToken = UtLocalCacheCalloc (strlen (LineToken) + 1);
            strcpy (FinalLineToken, LineToken);

            /* Get rid of any carriage returns */

            if (FinalLineToken[strlen (FinalLineToken) - 1] == 0x0D)
            {
                FinalLineToken[strlen(FinalLineToken)-1] = 0;
            }

            CvAddToCommentList (FinalLineToken);
            LineToken = strtok (NULL, "\n");
            while (LineToken != NULL)
            {
                /*
                 * It is assumed that each line has some sort of indentation.
                 * This means that we need to find the first character that
                 * is not a white space within each line.
                 */
                CharStart = FALSE;
                for (i = 0; (i < (strlen (LineToken) + 1)) && !CharStart; i++)
                {
                    if (LineToken[i] != ' ' && LineToken[i] != '\t')
                    {
                        CharStart = TRUE;
                        LineToken += i-1;
                        LineToken [0] = ' '; /* Pad for Formatting */
                    }
                }

                FinalLineToken = UtLocalCacheCalloc (strlen (LineToken) + 1);
                strcat (FinalLineToken, LineToken);

                /* Get rid of any carriage returns */

                if (FinalLineToken[strlen (FinalLineToken) - 1] == 0x0D)
                {
                    FinalLineToken[strlen(FinalLineToken) - 1] = 0;
                }

                CvAddToCommentList (FinalLineToken);
                LineToken = strtok (NULL,"\n");
            }
        }

        /*
         * If this only spans a single line, check to see whether if this
         * comment appears on the same line as a line of code. If does,
         * retain it's position for stylistic reasons. If it doesn't,
         * add it to the comment list so that it can be associated with
         * the next node that's created.
         */
        else
        {
           /*
            * If this is not a regular comment, pad with extra spaces that
            * appeared in the original source input to retain the original
            * spacing.
            */
            FinalCommentString =
                UtLocalCacheCalloc (strlen (CommentString) +
                CurrentState.SpacesBefore + 1);

            for (i = 0; (CurrentState.CommentType != ASL_COMMENT_STANDARD) &&
                (i < CurrentState.SpacesBefore); i++)
            {
                 FinalCommentString[i] = ' ';
            }

            strcat (FinalCommentString, CommentString);
            CvPlaceComment (CurrentState.CommentType, FinalCommentString);
        }
    }
}