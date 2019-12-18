#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nLists; int /*<<< orphan*/ * pSearch; } ;
struct TYPE_8__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  TYPE_2__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FICL_DEFAULT_VOCS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dictResetSearchOrder (TYPE_2__*) ; 
 int /*<<< orphan*/  ficlLockDictionary (int /*<<< orphan*/ ) ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPopPtr (int /*<<< orphan*/ ) ; 
 TYPE_2__* vmGetDict (TYPE_1__*) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*) ; 

__attribute__((used)) static void setOrder(FICL_VM *pVM)
{
    int i;
    int nLists = stackPopINT(pVM->pStack);
    FICL_DICT *dp = vmGetDict(pVM);

    if (nLists > FICL_DEFAULT_VOCS)
    {
        vmThrowErr(pVM, "set-order error: list would be too large");
    }

    ficlLockDictionary(TRUE);

    if (nLists >= 0)
    {
        dp->nLists = nLists;
        for (i = nLists-1; i >= 0; --i)
        {
            dp->pSearch[i] = stackPopPtr(pVM->pStack);
        }
    }
    else
    {
        dictResetSearchOrder(dp);
    }

    ficlLockDictionary(FALSE);
    return;
}