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
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t AE_OK ; 
 size_t ASL_EOF ; 
 size_t ASL_IGNORE_LINE ; 
 int AcpiGbl_LineScanState ; 
 char* AslGbl_CurrentLineBuffer ; 
 size_t AslGbl_LineBufferSize ; 
 int EOF ; 
#define  PR_MULTI_LINE_COMMENT 131 
#define  PR_NORMAL_TEXT 130 
#define  PR_QUOTED_STRING 129 
#define  PR_SINGLE_LINE_COMMENT 128 
 int /*<<< orphan*/  UtExpandLineBuffers () ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static UINT32
PrGetNextLine (
    FILE                    *Handle)
{
    UINT32                  i;
    int                     c = 0;
    int                     PreviousChar;


    /* Always clear the global line buffer */

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

        PreviousChar = c;
        c = getc (Handle);
        if (c == EOF)
        {
            /*
             * On EOF: If there is anything in the line buffer, terminate
             * it with a newline, and catch the EOF on the next call
             * to this function.
             */
            if (i > 0)
            {
                AslGbl_CurrentLineBuffer[i] = '\n';
                return (AE_OK);
            }

            return (ASL_EOF);
        }

        /* Update state machine as necessary */

        switch (AcpiGbl_LineScanState)
        {
        case PR_NORMAL_TEXT:

            /* Check for multi-line comment start */

            if ((PreviousChar == '/') && (c == '*'))
            {
                AcpiGbl_LineScanState = PR_MULTI_LINE_COMMENT;
            }

            /* Check for single-line comment start */

            else if ((PreviousChar == '/') && (c == '/'))
            {
                AcpiGbl_LineScanState = PR_SINGLE_LINE_COMMENT;
            }

            /* Check for quoted string start */

            else if (PreviousChar == '"')
            {
                AcpiGbl_LineScanState = PR_QUOTED_STRING;
            }
            break;

        case PR_QUOTED_STRING:

            if (PreviousChar == '"')
            {
                AcpiGbl_LineScanState = PR_NORMAL_TEXT;
            }
            break;

        case PR_MULTI_LINE_COMMENT:

            /* Check for multi-line comment end */

            if ((PreviousChar == '*') && (c == '/'))
            {
                AcpiGbl_LineScanState = PR_NORMAL_TEXT;
            }
            break;

        case PR_SINGLE_LINE_COMMENT: /* Just ignore text until EOL */
        default:
            break;
        }

        /* Always copy the character into line buffer */

        AslGbl_CurrentLineBuffer[i] = (char) c;
        i++;

        /* Always exit on end-of-line */

        if (c == '\n')
        {
            /* Handle multi-line comments */

            if (AcpiGbl_LineScanState == PR_MULTI_LINE_COMMENT)
            {
                return (ASL_IGNORE_LINE);
            }

            /* End of single-line comment */

            if (AcpiGbl_LineScanState == PR_SINGLE_LINE_COMMENT)
            {
                AcpiGbl_LineScanState = PR_NORMAL_TEXT;
                return (AE_OK);
            }

            /* Blank line */

            if (i == 1)
            {
                return (ASL_IGNORE_LINE);
            }

            return (AE_OK);
        }
    }
}