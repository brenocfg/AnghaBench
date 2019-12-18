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
struct TYPE_4__ {struct TYPE_4__* fStack; struct TYPE_4__* rStack; struct TYPE_4__* pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  ficlFree (TYPE_1__*) ; 

void vmDelete (FICL_VM *pVM)
{
    if (pVM)
    {
        ficlFree(pVM->pStack);
        ficlFree(pVM->rStack);
#if FICL_WANT_FLOAT
        ficlFree(pVM->fStack);
#endif
        ficlFree(pVM);
    }

    return;
}