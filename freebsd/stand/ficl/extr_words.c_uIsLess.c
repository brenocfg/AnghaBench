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
struct TYPE_4__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  scalar_t__ FICL_UNS ;

/* Variables and functions */
 int /*<<< orphan*/  FICL_BOOL (int) ; 
 int /*<<< orphan*/  PUSHINT (int /*<<< orphan*/ ) ; 
 scalar_t__ stackPopUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void uIsLess(FICL_VM *pVM)
{
    FICL_UNS u1, u2;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 2, 1);
#endif
    u2 = stackPopUNS(pVM->pStack);
    u1 = stackPopUNS(pVM->pStack);
    PUSHINT(FICL_BOOL(u1 < u2));
    return;
}