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
typedef  int /*<<< orphan*/  FICL_UNS ;
typedef  int /*<<< orphan*/  DPUNS ;

/* Variables and functions */
 int /*<<< orphan*/  POPUNS () ; 
 int /*<<< orphan*/  ficlLongMul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64Push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void umStar(FICL_VM *pVM)
{
    FICL_UNS u2;
    FICL_UNS u1;
    DPUNS ud;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,2,2);
#endif

    u2 = POPUNS();
    u1 = POPUNS();

    ud = ficlLongMul(u1, u2);
    u64Push(pVM->pStack, ud);
    return;
}