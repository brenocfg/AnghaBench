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
typedef  char UINT8 ;
typedef  size_t UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  FlPrintFile (size_t,char*,...) ; 
 scalar_t__ isprint (char) ; 

void
LsDumpAsciiInComment (
    UINT32                  FileId,
    UINT32                  Count,
    UINT8                   *Buffer)
{
    UINT8                   BufChar = 0;
    UINT8                   LastChar;
    UINT32                  i;


    FlPrintFile (FileId, "    \"");
    for (i = 0; i < Count; i++)
    {
        LastChar = BufChar;
        BufChar = Buffer[i];

        if (isprint (BufChar))
        {
            /* Handle embedded C comment sequences */

            if (((LastChar == '*') && (BufChar == '/')) ||
                ((LastChar == '/') && (BufChar == '*')))
            {
                /* Insert a space to break the sequence */

                FlPrintFile (FileId, " ");
            }

            FlPrintFile (FileId, "%c", BufChar);
        }
        else
        {
            /* Not a printable character, just put out a dot */

            FlPrintFile (FileId, ".");
        }
    }

    FlPrintFile (FileId, "\"");
}