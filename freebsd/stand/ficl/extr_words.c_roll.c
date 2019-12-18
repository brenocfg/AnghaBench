#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i; } ;
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 TYPE_3__ stackPop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackRoll (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void roll(FICL_VM *pVM)
{
    int i = stackPop(pVM->pStack).i;
    i = (i > 0) ? i : 0;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, i+1, i+1);
#endif
    stackRoll(pVM->pStack, i);
    return;
}