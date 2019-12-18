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

/* Variables and functions */
 int /*<<< orphan*/  delay (int) ; 
 int stackPopUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ms(FICL_VM *pVM)
{
#if FICL_ROBUST > 1
    vmCheckStack(pVM,1,0);
#endif
#ifdef TESTMAIN
    usleep(stackPopUNS(pVM->pStack)*1000);
#else
    delay(stackPopUNS(pVM->pStack)*1000);
#endif
    return;
}