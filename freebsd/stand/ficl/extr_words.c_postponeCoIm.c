#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * p; } ;
struct TYPE_7__ {int /*<<< orphan*/  pStack; int /*<<< orphan*/  pSys; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ficlLookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ficlTick (TYPE_1__*) ; 
 int /*<<< orphan*/  literalIm (TYPE_1__*) ; 
 TYPE_3__ stackGetTop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_1__*) ; 
 scalar_t__ wordIsImmediate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void postponeCoIm(FICL_VM *pVM)
{
    FICL_DICT *dp  = vmGetDict(pVM);
    FICL_WORD *pFW;
    FICL_WORD *pComma = ficlLookup(pVM->pSys, ",");
    assert(pComma);

    ficlTick(pVM);
    pFW = stackGetTop(pVM->pStack).p;
    if (wordIsImmediate(pFW))
    {
        dictAppendCell(dp, stackPop(pVM->pStack));
    }
    else
    {
        literalIm(pVM);
        dictAppendCell(dp, LVALUEtoCELL(pComma));
    }
    
    return;
}