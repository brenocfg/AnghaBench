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
struct TYPE_7__ {TYPE_1__* pSys; } ;
struct TYPE_6__ {scalar_t__ nLocals; int /*<<< orphan*/  pExitParen; int /*<<< orphan*/  pUnLinkParen; } ;
typedef  TYPE_2__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE (TYPE_2__*) ; 
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_2__*) ; 

__attribute__((used)) static void exitCoIm(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
    assert(pVM->pSys->pExitParen);
    IGNORE(pVM);

#if FICL_WANT_LOCALS
    if (pVM->pSys->nLocals > 0)
    {
        dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pUnLinkParen));
    }
#endif
    dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pExitParen));
    return;
}