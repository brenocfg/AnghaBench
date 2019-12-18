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
struct TYPE_3__ {int /*<<< orphan*/  here; } ;
typedef  int /*<<< orphan*/  FICL_VM ;
typedef  TYPE_1__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* vmGetDict (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void here(FICL_VM *pVM)
{
    FICL_DICT *dp;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 0, 1);
#endif

    dp = vmGetDict(pVM);
    PUSHPTR(dp->here);
    return;
}