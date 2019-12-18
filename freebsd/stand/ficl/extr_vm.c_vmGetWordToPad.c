#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pad; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 size_t SI_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,size_t) ; 
 size_t nPAD ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vmGetWord (TYPE_1__*) ; 

int vmGetWordToPad(FICL_VM *pVM)
{
    STRINGINFO si;
    char *cp = (char *)pVM->pad;
    si = vmGetWord(pVM);

    if (SI_COUNT(si) > nPAD)
        SI_SETLEN(si, nPAD);

    strncpy(cp, SI_PTR(si), SI_COUNT(si));
    cp[SI_COUNT(si)] = '\0';
    return (int)(SI_COUNT(si));
}