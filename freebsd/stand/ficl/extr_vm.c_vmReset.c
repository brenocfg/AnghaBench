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
struct TYPE_4__ {int base; int /*<<< orphan*/  fStack; int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  stackReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmQuit (TYPE_1__*) ; 

void vmReset(FICL_VM *pVM)
{
    vmQuit(pVM);
    stackReset(pVM->pStack);
#if FICL_WANT_FLOAT
    stackReset(pVM->fStack);
#endif
    pVM->base        = 10;
    return;
}