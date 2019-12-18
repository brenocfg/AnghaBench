#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FICL_VM ;
typedef  scalar_t__ FICL_INT ;

/* Variables and functions */
 scalar_t__ POPINT () ; 
 int /*<<< orphan*/  PUSHINT (int) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void sToD(FICL_VM *pVM)
{
    FICL_INT s;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,1,2);
#endif

    s = POPINT();

    /* sign extend to 64 bits.. */
    PUSHINT(s);
    PUSHINT((s < 0) ? -1 : 0);
    return;
}