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
typedef  int /*<<< orphan*/  FICL_INT ;
typedef  int /*<<< orphan*/  DPINT ;

/* Variables and functions */
 int /*<<< orphan*/  POPINT () ; 
 int /*<<< orphan*/  i64Push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m64MulI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void mStar(FICL_VM *pVM)
{
    FICL_INT n2;
    FICL_INT n1;
    DPINT d;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,2,2);
#endif

    n2 = POPINT();
    n1 = POPINT();

    d = m64MulI(n1, n2);
    i64Push(pVM->pStack, d);
    return;
}