#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  quot; } ;
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_INT ;
typedef  int /*<<< orphan*/  DPINT ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m64MulI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ m64SymmetricDivI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void mulDiv(FICL_VM *pVM)
{
    FICL_INT x, y, z;
    DPINT prod;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 3, 1);
#endif
    z = stackPopINT(pVM->pStack);
    y = stackPopINT(pVM->pStack);
    x = stackPopINT(pVM->pStack);

    prod = m64MulI(x,y);
    x    = m64SymmetricDivI(prod, z).quot;

    PUSHINT(x);
    return;
}