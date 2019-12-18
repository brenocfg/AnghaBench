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
struct vmspace {scalar_t__ vm_refcnt; } ;

/* Variables and functions */
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int atomic_fetchadd_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vmspace_dofree (struct vmspace*) ; 

void
vmspace_free(struct vmspace *vm)
{

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "vmspace_free() called");

	if (vm->vm_refcnt == 0)
		panic("vmspace_free: attempt to free already freed vmspace");

	if (atomic_fetchadd_int(&vm->vm_refcnt, -1) == 1)
		vmspace_dofree(vm);
}