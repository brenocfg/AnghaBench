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
struct TYPE_7__ {int /*<<< orphan*/  i; } ;
struct TYPE_6__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  TYPE_2__ CELL ;

/* Variables and functions */
 int /*<<< orphan*/  FICL_BOOL (int) ; 
 scalar_t__ stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPush (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void zeroLess(FICL_VM *pVM)
{
    CELL c;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 1);
#endif
    c.i = FICL_BOOL(stackPopINT(pVM->pStack) < 0);
    stackPush(pVM->pStack, c);
    return;
}