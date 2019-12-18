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
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* UtLocalCalloc (scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
DtNormalizeBuffer (
    char                    *Buffer,
    UINT32                  *Count)
{
    char                    *NewBuffer;
    char                    *TmpBuffer;
    UINT32                  BufferCount = 0;
    BOOLEAN                 Separator = TRUE;
    char                    c;


    NewBuffer = UtLocalCalloc (strlen (Buffer) + 1);
    TmpBuffer = NewBuffer;

    while ((c = *Buffer++))
    {
        switch (c)
        {
        /* Valid separators */

        case '[':
        case ']':
        case ' ':
        case ',':

            Separator = TRUE;
            break;

        default:

            if (Separator)
            {
                /* Insert blank as the standard separator */

                if (NewBuffer[0])
                {
                    *TmpBuffer++ = ' ';
                    BufferCount++;
                }

                Separator = FALSE;
            }

            *TmpBuffer++ = c;
            break;
        }
    }

    *Count = BufferCount + 1;
    return (NewBuffer);
}