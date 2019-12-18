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
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 int SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SI_SETPTR (int /*<<< orphan*/ ,char*) ; 
 char* vmGetInBuf (int /*<<< orphan*/ *) ; 
 char* vmGetInBufEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmUpdateTib (int /*<<< orphan*/ *,char*) ; 

STRINGINFO vmParseStringEx(FICL_VM *pVM, char delim, char fSkipLeading)
{
    STRINGINFO si;
    char *pSrc      = vmGetInBuf(pVM);
    char *pEnd      = vmGetInBufEnd(pVM);
    char ch;

    if (fSkipLeading)
    {                       /* skip lead delimiters */
        while ((pSrc != pEnd) && (*pSrc == delim))
            pSrc++;
    }

    SI_SETPTR(si, pSrc);    /* mark start of text */

    for (ch = *pSrc; (pSrc != pEnd)
                  && (ch != delim)
                  && (ch != '\r') 
                  && (ch != '\n'); ch = *++pSrc)
    {
        ;                   /* find next delimiter or end of line */
    }

                            /* set length of result */
    SI_SETLEN(si, pSrc - SI_PTR(si));

    if ((pSrc != pEnd) && (*pSrc == delim))     /* gobble trailing delimiter */
        pSrc++;

    vmUpdateTib(pVM, pSrc);
    return si;
}