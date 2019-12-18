#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pStack; int /*<<< orphan*/  rStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  stackPop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackRoll (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twoToR(FICL_VM *pVM)
{
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 2, 0);
#endif
    stackRoll(pVM->pStack, 1);
    stackPush(pVM->rStack, stackPop(pVM->pStack));
    stackPush(pVM->rStack, stackPop(pVM->pStack));
    return;
}