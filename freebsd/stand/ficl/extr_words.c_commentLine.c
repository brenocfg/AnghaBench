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
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 char* vmGetInBuf (int /*<<< orphan*/ *) ; 
 char* vmGetInBufEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmUpdateTib (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void commentLine(FICL_VM *pVM)
{
    char *cp        = vmGetInBuf(pVM);
    char *pEnd      = vmGetInBufEnd(pVM);
    char ch = *cp;

    while ((cp != pEnd) && (ch != '\r') && (ch != '\n'))
    {
        ch = *++cp;
    }

    /*
    ** Cope with DOS or UNIX-style EOLs -
    ** Check for /r, /n, /r/n, or /n/r end-of-line sequences,
    ** and point cp to next char. If EOL is \0, we're done.
    */
    if (cp != pEnd)
    {
        cp++;

        if ( (cp != pEnd) && (ch != *cp) 
             && ((*cp == '\r') || (*cp == '\n')) )
            cp++;
    }

    vmUpdateTib(pVM, cp);
    return;
}