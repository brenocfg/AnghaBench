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
typedef  scalar_t__ FICL_UNS ;

/* Variables and functions */
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SI_SETPTR (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isspace (char) ; 
 char* skipSpace (char*,char*) ; 
 char* vmGetInBuf (int /*<<< orphan*/ *) ; 
 char* vmGetInBufEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmUpdateTib (int /*<<< orphan*/ *,char*) ; 

STRINGINFO vmGetWord0(FICL_VM *pVM)
{
    char *pSrc      = vmGetInBuf(pVM);
    char *pEnd      = vmGetInBufEnd(pVM);
    STRINGINFO si;
    FICL_UNS count = 0;
    char ch = 0;

    pSrc = skipSpace(pSrc, pEnd);
    SI_SETPTR(si, pSrc);

/*
    for (ch = *pSrc; (pEnd != pSrc) && !isspace(ch); ch = *++pSrc)
    {
        count++;
    }
*/

    /* Changed to make Purify happier.  --lch */
    for (;;)
    {
        if (pEnd == pSrc)
            break;
        ch = *pSrc;
        if (isspace(ch))
            break;
        count++;
        pSrc++;
    }

    SI_SETLEN(si, count);

    if ((pEnd != pSrc) && isspace(ch))    /* skip one trailing delimiter */
        pSrc++;

    vmUpdateTib(pVM, pSrc);

    return si;
}