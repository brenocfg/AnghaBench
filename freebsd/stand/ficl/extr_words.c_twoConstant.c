#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pStack; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DEFAULT ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendWord2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twoConstParen ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_1__*) ; 
 int /*<<< orphan*/  vmGetWord (TYPE_1__*) ; 

__attribute__((used)) static void twoConstant(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
    STRINGINFO si = vmGetWord(pVM);
    CELL c;
    
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 2, 0);
#endif
    c = stackPop(pVM->pStack);
    dictAppendWord2(dp, si, twoConstParen, FW_DEFAULT);
    dictAppendCell(dp, stackPop(pVM->pStack));
    dictAppendCell(dp, c);
    return;
}