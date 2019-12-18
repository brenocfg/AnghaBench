#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ p; } ;
struct TYPE_6__ {int /*<<< orphan*/  pSys; int /*<<< orphan*/  pStack; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  ficlAddParseStep (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isAFiclWord (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ stackPop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_1__*) ; 

__attribute__((used)) static void addParseStep(FICL_VM *pVM)
{
    FICL_WORD *pStep;
    FICL_DICT *pd = vmGetDict(pVM);
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif
    pStep = (FICL_WORD *)(stackPop(pVM->pStack).p);
    if ((pStep != NULL) && isAFiclWord(pd, pStep))
        ficlAddParseStep(pVM->pSys, pStep);
    return;
}