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
struct TYPE_7__ {int /*<<< orphan*/  pStack; } ;
struct TYPE_6__ {int /*<<< orphan*/  quot; int /*<<< orphan*/  rem; } ;
typedef  TYPE_1__ INTQR ;
typedef  TYPE_2__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_INT ;
typedef  int /*<<< orphan*/  DPINT ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m64MulI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ m64SymmetricDivI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_2__*,int,int) ; 

__attribute__((used)) static void mulDivRem(FICL_VM *pVM)
{
    FICL_INT x, y, z;
    DPINT prod;
    INTQR qr;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 3, 2);
#endif
    z = stackPopINT(pVM->pStack);
    y = stackPopINT(pVM->pStack);
    x = stackPopINT(pVM->pStack);

    prod = m64MulI(x,y);
    qr   = m64SymmetricDivI(prod, z);

    PUSHINT(qr.rem);
    PUSHINT(qr.quot);
    return;
}