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

/* Variables and functions */
 scalar_t__ strchr (char*,char) ; 

char *
PrGetNextToken (
    char                    *Buffer,
    char                    *MatchString,
    char                    **Next)
{
    char                    *TokenStart;


    if (!Buffer)
    {
        /* Use Next if it is valid */

        Buffer = *Next;
        if (!(*Next))
        {
            return (NULL);
        }
    }

    /* Skip any leading delimiters */

    while (*Buffer)
    {
        if (strchr (MatchString, *Buffer))
        {
            Buffer++;
        }
        else
        {
            break;
        }
    }

    /* Anything left on the line? */

    if (!(*Buffer))
    {
        *Next = NULL;
        return (NULL);
    }

    TokenStart = Buffer;

    /* Find the end of this token */

    while (*Buffer)
    {
        if (strchr (MatchString, *Buffer))
        {
            *Buffer = 0;
            *Next = Buffer+1;
            if (!**Next)
            {
                *Next = NULL;
            }

            return (TokenStart);
        }

        Buffer++;
    }

    *Next = NULL;
    return (TokenStart);
}