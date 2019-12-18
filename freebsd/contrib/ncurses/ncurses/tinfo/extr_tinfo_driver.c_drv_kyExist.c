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
struct TYPE_3__ {scalar_t__ csp; } ;
typedef  TYPE_1__ TERMINAL_CONTROL_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int FALSE ; 
 scalar_t__ TINFO_HAS_KEY (scalar_t__,int) ; 
 int TRUE ; 

__attribute__((used)) static bool
drv_kyExist(TERMINAL_CONTROL_BLOCK * TCB, int key)
{
    bool res = FALSE;

    AssertTCB();
    if (TCB->csp)
	res = TINFO_HAS_KEY(TCB->csp, key) == 0 ? FALSE : TRUE;

    return res;
}