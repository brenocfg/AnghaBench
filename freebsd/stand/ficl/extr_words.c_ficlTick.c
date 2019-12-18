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
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHPTR (int /*<<< orphan*/ *) ; 
 int SI_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmGetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmGetWord (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmThrowErr (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

void ficlTick(FICL_VM *pVM)
{
    FICL_WORD *pFW = NULL;
    STRINGINFO si = vmGetWord(pVM);
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 0, 1);
#endif

    pFW = dictLookup(vmGetDict(pVM), si);
    if (!pFW)
    {
        int i = SI_COUNT(si);
        vmThrowErr(pVM, "%.*s not found", i, SI_PTR(si));
    }
    PUSHPTR(pFW);
    return;
}