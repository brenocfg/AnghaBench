#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pStack; TYPE_1__* pSys; } ;
struct TYPE_5__ {int /*<<< orphan*/  pTwoLitParen; } ;
typedef  TYPE_2__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_2__*) ; 

__attribute__((used)) static void twoLiteralIm(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
    assert(pVM->pSys->pTwoLitParen);

    dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pTwoLitParen));
    dictAppendCell(dp, stackPop(pVM->pStack));
    dictAppendCell(dp, stackPop(pVM->pStack));

    return;
}