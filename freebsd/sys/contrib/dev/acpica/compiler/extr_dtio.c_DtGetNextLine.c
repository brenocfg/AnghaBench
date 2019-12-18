#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ASL_EOF ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,scalar_t__) ; 
 char* AslGbl_CurrentLineBuffer ; 
 int /*<<< orphan*/  AslGbl_CurrentLineNumber ; 
 scalar_t__ AslGbl_LineBufferSize ; 
 scalar_t__ AslGbl_NextLineOffset ; 
 scalar_t__ DT_ALLOW_MULTILINE_QUOTES ; 
#define  DT_END_COMMENT 135 
#define  DT_ESCAPE_SEQUENCE 134 
#define  DT_MERGE_LINES 133 
#define  DT_NORMAL_TEXT 132 
#define  DT_SLASH_ASTERISK_COMMENT 131 
#define  DT_SLASH_SLASH_COMMENT 130 
#define  DT_START_COMMENT 129 
#define  DT_START_QUOTED_STRING 128 
 int /*<<< orphan*/  DtFatal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int EOF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UtExpandLineBuffers () ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

UINT32
DtGetNextLine (
    FILE                    *Handle,
    UINT32                  Flags)
{
    BOOLEAN                 LineNotAllBlanks = FALSE;
    UINT32                  State = DT_NORMAL_TEXT;
    UINT32                  CurrentLineOffset;
    UINT32                  i;
    int                     c;
    int                     c1;


    memset (AslGbl_CurrentLineBuffer, 0, AslGbl_LineBufferSize);
    for (i = 0; ;)
    {
        /*
         * If line is too long, expand the line buffers. Also increases
         * AslGbl_LineBufferSize.
         */
        if (i >= AslGbl_LineBufferSize)
        {
            UtExpandLineBuffers ();
        }

        c = getc (Handle);
        if (c == EOF)
        {
            switch (State)
            {
            case DT_START_QUOTED_STRING:
            case DT_SLASH_ASTERISK_COMMENT:

                AcpiOsPrintf ("**** EOF within comment/string %u\n", State);
                break;

            default:

                break;
            }

            /* Standalone EOF is OK */

            if (i == 0)
            {
                return (ASL_EOF);
            }

            /*
             * Received an EOF in the middle of a line. Terminate the
             * line with a newline. The next call to this function will
             * return a standalone EOF. Thus, the upper parsing software
             * never has to deal with an EOF within a valid line (or
             * the last line does not get tossed on the floor.)
             */
            c = '\n';
            State = DT_NORMAL_TEXT;
        }
        else if (c == '\r')
        {
            c1 = getc (Handle);
            if (c1 == '\n')
            {
                /*
                 * Skip the carriage return as if it didn't exist. This is
                 * onlt meant for input files in DOS format in unix. fopen in
                 * unix may not support "text mode" and leaves CRLF intact.
                 */
                c = '\n';
            }
            else
            {
                /* This was not a CRLF. Only a CR */

                ungetc(c1, Handle);

                DtFatal (ASL_MSG_COMPILER_INTERNAL, NULL,
                    "Carriage return without linefeed detected");
                return (ASL_EOF);
            }
        }

        switch (State)
        {
        case DT_NORMAL_TEXT:

            /* Normal text, insert char into line buffer */

            AslGbl_CurrentLineBuffer[i] = (char) c;
            switch (c)
            {
            case '/':

                State = DT_START_COMMENT;
                break;

            case '"':

                State = DT_START_QUOTED_STRING;
                LineNotAllBlanks = TRUE;
                i++;
                break;

            case '\\':
                /*
                 * The continuation char MUST be last char on this line.
                 * Otherwise, it will be assumed to be a valid ASL char.
                 */
                State = DT_MERGE_LINES;
                break;

            case '\n':

                CurrentLineOffset = AslGbl_NextLineOffset;
                AslGbl_NextLineOffset = (UINT32) ftell (Handle);
                AslGbl_CurrentLineNumber++;

                /*
                 * Exit if line is complete. Ignore empty lines (only \n)
                 * or lines that contain nothing but blanks.
                 */
                if ((i != 0) && LineNotAllBlanks)
                {
                    if ((i + 1) >= AslGbl_LineBufferSize)
                    {
                        UtExpandLineBuffers ();
                    }

                    AslGbl_CurrentLineBuffer[i+1] = 0; /* Terminate string */
                    return (CurrentLineOffset);
                }

                /* Toss this line and start a new one */

                i = 0;
                LineNotAllBlanks = FALSE;
                break;

            default:

                if (c != ' ')
                {
                    LineNotAllBlanks = TRUE;
                }

                i++;
                break;
            }
            break;

        case DT_START_QUOTED_STRING:

            /* Insert raw chars until end of quoted string */

            AslGbl_CurrentLineBuffer[i] = (char) c;
            i++;

            switch (c)
            {
            case '"':

                State = DT_NORMAL_TEXT;
                break;

            case '\\':

                State = DT_ESCAPE_SEQUENCE;
                break;

            case '\n':

                if (!(Flags & DT_ALLOW_MULTILINE_QUOTES))
                {
                    AcpiOsPrintf (
                        "ERROR at line %u: Unterminated quoted string\n",
                        AslGbl_CurrentLineNumber++);
                    State = DT_NORMAL_TEXT;
                }
                break;

            default:    /* Get next character */

                break;
            }
            break;

        case DT_ESCAPE_SEQUENCE:

            /* Just copy the escaped character. TBD: sufficient for table compiler? */

            AslGbl_CurrentLineBuffer[i] = (char) c;
            i++;
            State = DT_START_QUOTED_STRING;
            break;

        case DT_START_COMMENT:

            /* Open comment if this character is an asterisk or slash */

            switch (c)
            {
            case '*':

                State = DT_SLASH_ASTERISK_COMMENT;
                break;

            case '/':

                State = DT_SLASH_SLASH_COMMENT;
                break;

            default:    /* Not a comment */

                i++;    /* Save the preceding slash */
                if (i >= AslGbl_LineBufferSize)
                {
                    UtExpandLineBuffers ();
                }

                AslGbl_CurrentLineBuffer[i] = (char) c;
                i++;
                State = DT_NORMAL_TEXT;
                break;
            }
            break;

        case DT_SLASH_ASTERISK_COMMENT:

            /* Ignore chars until an asterisk-slash is found */

            switch (c)
            {
            case '\n':

                AslGbl_NextLineOffset = (UINT32) ftell (Handle);
                AslGbl_CurrentLineNumber++;
                break;

            case '*':

                State = DT_END_COMMENT;
                break;

            default:

                break;
            }
            break;

        case DT_SLASH_SLASH_COMMENT:

            /* Ignore chars until end-of-line */

            if (c == '\n')
            {
                /* We will exit via the NORMAL_TEXT path */

                ungetc (c, Handle);
                State = DT_NORMAL_TEXT;
            }
            break;

        case DT_END_COMMENT:

            /* End comment if this char is a slash */

            switch (c)
            {
            case '/':

                State = DT_NORMAL_TEXT;
                break;

            case '\n':

                AslGbl_NextLineOffset = (UINT32) ftell (Handle);
                AslGbl_CurrentLineNumber++;
                break;

            case '*':

                /* Consume all adjacent asterisks */
                break;

            default:

                State = DT_SLASH_ASTERISK_COMMENT;
                break;
            }
            break;

        case DT_MERGE_LINES:

            if (c != '\n')
            {
                /*
                 * This is not a continuation backslash, it is a normal
                 * normal ASL backslash - for example: Scope(\_SB_)
                 */
                i++; /* Keep the backslash that is already in the buffer */

                ungetc (c, Handle);
                State = DT_NORMAL_TEXT;
            }
            else
            {
                /*
                 * This is a continuation line -- a backlash followed
                 * immediately by a newline. Insert a space between the
                 * lines (overwrite the backslash)
                 */
                AslGbl_CurrentLineBuffer[i] = ' ';
                i++;

                /* Ignore newline, this will merge the lines */

                AslGbl_NextLineOffset = (UINT32) ftell (Handle);
                AslGbl_CurrentLineNumber++;
                State = DT_NORMAL_TEXT;
            }
            break;

        default:

            DtFatal (ASL_MSG_COMPILER_INTERNAL, NULL, "Unknown input state");
            return (ASL_EOF);
        }
    }
}