#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ param; } ;
typedef  TYPE_1__ FICL_WORD ;
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 TYPE_1__* POPPTR () ; 
 int /*<<< orphan*/  PUSHPTR (scalar_t__) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void toBody(FICL_VM *pVM)
{
    FICL_WORD *pFW;
/*#$-GUY CHANGE: Added robustness.-$#*/
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 1);
#endif

    pFW = POPPTR();
    PUSHPTR(pFW->param + 1);
    return;
}