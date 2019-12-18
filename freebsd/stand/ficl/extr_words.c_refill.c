#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i; } ;
struct TYPE_6__ {scalar_t__ fRestart; TYPE_1__ sourceID; } ;
typedef  TYPE_2__ FICL_VM ;
typedef  scalar_t__ FICL_INT ;

/* Variables and functions */
 scalar_t__ FICL_FALSE ; 
 scalar_t__ FICL_TRUE ; 
 int /*<<< orphan*/  PUSHINT (scalar_t__) ; 
 int /*<<< orphan*/  VM_RESTART ; 
 int /*<<< orphan*/  vmThrow (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void refill(FICL_VM *pVM)
{
    FICL_INT ret = (pVM->sourceID.i == -1) ? FICL_FALSE : FICL_TRUE;
    if (ret && (pVM->fRestart == 0))
        vmThrow(pVM, VM_RESTART);

    PUSHINT(ret);
    return;
}