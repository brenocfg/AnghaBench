#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ nLocals; int /*<<< orphan*/  pStore; int /*<<< orphan*/  pTo2LocalParen; int /*<<< orphan*/  pToLocalParen; } ;
struct TYPE_11__ {scalar_t__ state; TYPE_8__* pSys; int /*<<< orphan*/  pStack; } ;
struct TYPE_10__ {scalar_t__ code; int /*<<< orphan*/ * param; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  TYPE_1__ FICL_WORD ;
typedef  TYPE_2__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 scalar_t__ COMPILE ; 
 scalar_t__ INTERPRET ; 
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSHPTR (int /*<<< orphan*/ *) ; 
 int SI_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* dictLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ do2LocalIm ; 
 scalar_t__ doLocalIm ; 
 int /*<<< orphan*/ * ficlGetLoc (TYPE_8__*) ; 
 int /*<<< orphan*/  literalIm (TYPE_2__*) ; 
 int /*<<< orphan*/  stackPop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_2__*) ; 
 int /*<<< orphan*/  vmGetWord (TYPE_2__*) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toValue(FICL_VM *pVM)
{
    STRINGINFO si = vmGetWord(pVM);
    FICL_DICT *dp = vmGetDict(pVM);
    FICL_WORD *pFW;

#if FICL_WANT_LOCALS
    if ((pVM->pSys->nLocals > 0) && (pVM->state == COMPILE))
    {
        FICL_DICT *pLoc = ficlGetLoc(pVM->pSys);
        pFW = dictLookup(pLoc, si);
        if (pFW && (pFW->code == doLocalIm))
        {
            dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pToLocalParen));
            dictAppendCell(dp, LVALUEtoCELL(pFW->param[0]));
            return;
        }
        else if (pFW && pFW->code == do2LocalIm)
        {
            dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pTo2LocalParen));
            dictAppendCell(dp, LVALUEtoCELL(pFW->param[0]));
            return;
        }
    }
#endif

    assert(pVM->pSys->pStore);

    pFW = dictLookup(dp, si);
    if (!pFW)
    {
        int i = SI_COUNT(si);
        vmThrowErr(pVM, "%.*s not found", i, SI_PTR(si));
    }

    if (pVM->state == INTERPRET)
        pFW->param[0] = stackPop(pVM->pStack);
    else        /* compile code to store to word's param */
    {
        PUSHPTR(&pFW->param[0]);
        literalIm(pVM);
        dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pStore));
    }
    return;
}