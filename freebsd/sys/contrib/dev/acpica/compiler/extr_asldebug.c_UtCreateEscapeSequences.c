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
typedef  int UINT32 ;

/* Variables and functions */
 char AcpiUtHexToAsciiChar (char,int) ; 
 char* UtLocalCacheCalloc (int) ; 

__attribute__((used)) static char *
UtCreateEscapeSequences (
    char                    *InString)
{
    char                    *String = InString;
    char                    *OutString;
    char                    *OutStringPtr;
    UINT32                  InStringLength = 0;
    UINT32                  EscapeCount = 0;


    /*
     * Determine up front how many escapes are within the string.
     * Obtain the input string length while doing so.
     */
    while (*String)
    {
        if ((*String <= 0x1F) || (*String >= 0x7F))
        {
            EscapeCount++;
        }

        InStringLength++;
        String++;
    }

    if (!EscapeCount)
    {
        return (InString); /* No escapes, nothing to do */
    }

    /* New string buffer, 3 extra chars per escape (4 total) */

    OutString = UtLocalCacheCalloc (InStringLength + (EscapeCount * 3));
    OutStringPtr = OutString;

    /* Convert non-ascii or non-printable chars to escape sequences */

    while (*InString)
    {
        if ((*InString <= 0x1F) || (*InString >= 0x7F))
        {
            /* Insert a \x hex escape sequence */

            OutStringPtr[0] = '\\';
            OutStringPtr[1] = 'x';
            OutStringPtr[2] = AcpiUtHexToAsciiChar (*InString, 4);
            OutStringPtr[3] = AcpiUtHexToAsciiChar (*InString, 0);
            OutStringPtr += 4;
        }
        else /* Normal ASCII character */
        {
            *OutStringPtr = *InString;
            OutStringPtr++;
        }

        InString++;
    }

    return (OutString);
}