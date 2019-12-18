#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nLists; int /*<<< orphan*/ * pSearch; } ;
struct TYPE_7__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  TYPE_2__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ficlLockDictionary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* vmGetDict (TYPE_1__*) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*) ; 

__attribute__((used)) static void searchPop(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
    int nLists;

    ficlLockDictionary(TRUE);
    nLists = dp->nLists;
    if (nLists == 0)
    {
        vmThrowErr(pVM, "search> error: empty search order");
    }
    stackPushPtr(pVM->pStack, dp->pSearch[--dp->nLists]);
    ficlLockDictionary(FALSE);
    return;
}