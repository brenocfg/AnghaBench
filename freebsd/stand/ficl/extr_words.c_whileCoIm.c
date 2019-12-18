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
struct TYPE_8__ {TYPE_1__* pSys; } ;
struct TYPE_7__ {int /*<<< orphan*/  pBranch0; } ;
typedef  TYPE_2__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendUNS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  markBranch (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  origTag ; 
 int /*<<< orphan*/  twoSwap (TYPE_2__*) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_2__*) ; 

__attribute__((used)) static void whileCoIm(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);

    assert(pVM->pSys->pBranch0);

    dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pBranch0));
    markBranch(dp, pVM, origTag);
    twoSwap(pVM);
    dictAppendUNS(dp, 1);
    return;
}