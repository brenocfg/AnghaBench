#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNS16 ;
struct TYPE_7__ {int /*<<< orphan*/  pStack; } ;
struct TYPE_6__ {void* cp; scalar_t__ count; } ;
typedef  TYPE_1__ STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_2__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_HASH ;
typedef  scalar_t__ FICL_COUNT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ficlLockDictionary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashHashCode (TYPE_1__) ; 
 int /*<<< orphan*/ * hashLookup (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ ) ; 
 void* stackPopPtr (int /*<<< orphan*/ ) ; 
 scalar_t__ stackPopUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stackPushUNS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wordIsImmediate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void searchWordlist(FICL_VM *pVM)
{
    STRINGINFO si;
    UNS16 hashCode;
    FICL_WORD *pFW;
    FICL_HASH *pHash = stackPopPtr(pVM->pStack);

    si.count         = (FICL_COUNT)stackPopUNS(pVM->pStack);
    si.cp            = stackPopPtr(pVM->pStack);
    hashCode         = hashHashCode(si);

    ficlLockDictionary(TRUE);
    pFW = hashLookup(pHash, si, hashCode);
    ficlLockDictionary(FALSE);

    if (pFW)
    {
        stackPushPtr(pVM->pStack, pFW);
        stackPushINT(pVM->pStack, (wordIsImmediate(pFW) ? 1 : -1));
    }
    else
    {
        stackPushUNS(pVM->pStack, 0);
    }

    return;
}