#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pStack; TYPE_1__* pSys; } ;
struct TYPE_9__ {int /*<<< orphan*/  cp; scalar_t__ count; } ;
struct TYPE_8__ {int /*<<< orphan*/ * envp; } ;
typedef  TYPE_2__ STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_3__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;
typedef  scalar_t__ FICL_COUNT ;

/* Variables and functions */
 int /*<<< orphan*/  FICL_FALSE ; 
 int /*<<< orphan*/  FICL_TRUE ; 
 int /*<<< orphan*/  PUSHINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictLookup (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  stackPopPtr (int /*<<< orphan*/ ) ; 
 scalar_t__ stackPopUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  vmExecute (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void environmentQ(FICL_VM *pVM)
{
    FICL_DICT *envp;
    FICL_WORD *pFW;
    STRINGINFO si;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,2,1);
#endif

    envp = pVM->pSys->envp;
    si.count = (FICL_COUNT)stackPopUNS(pVM->pStack);
    si.cp    = stackPopPtr(pVM->pStack);

    pFW = dictLookup(envp, si);

    if (pFW != NULL)
    {
        vmExecute(pVM, pFW);
        PUSHINT(FICL_TRUE);
    }
    else
    {
        PUSHINT(FICL_FALSE);
    }
    return;
}