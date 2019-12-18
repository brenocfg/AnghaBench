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
typedef  void* vm_offset_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* arch_copyout ) (void*,void*,size_t) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 TYPE_4__ archsw ; 
 void* stackPopINT (int /*<<< orphan*/ ) ; 
 void* stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,void*,size_t) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void
ficlCopyout(FICL_VM *pVM)
{
	void*		dest;
	vm_offset_t	src;
	size_t		len;

#if FICL_ROBUST > 1
	vmCheckStack(pVM, 3, 0);
#endif

	len = stackPopINT(pVM->pStack);
	dest = stackPopPtr(pVM->pStack);
	src = stackPopINT(pVM->pStack);

#ifndef TESTMAIN
	archsw.arch_copyout(src, dest, len);
#endif

	return;
}