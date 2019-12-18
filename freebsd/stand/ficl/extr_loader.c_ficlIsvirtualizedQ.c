#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* (* arch_hypervisor ) () ;} ;
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_INT ;

/* Variables and functions */
 int /*<<< orphan*/  FICL_FALSE ; 
 int /*<<< orphan*/  FICL_TRUE ; 
 TYPE_4__ archsw ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub1 () ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ficlIsvirtualizedQ(FICL_VM *pVM)
{
	FICL_INT flag;
	const char *hv;

#if FICL_ROBUST > 1
	vmCheckStack(pVM, 0, 1);
#endif

	hv = (archsw.arch_hypervisor != NULL)
	    ? (*archsw.arch_hypervisor)()
	    : NULL;
	flag = (hv != NULL) ? FICL_TRUE : FICL_FALSE;
	stackPushINT(pVM->pStack, flag);
}