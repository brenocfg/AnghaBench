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
typedef  scalar_t__ vm_ooffset_t ;
struct vmspace {int vm_refcnt; } ;
struct proc {struct vmspace* p_vmspace; int /*<<< orphan*/  p_ucred; } ;
struct TYPE_3__ {struct proc* td_proc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PROC_VMSPACE_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_VMSPACE_UNLOCK (struct proc*) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  pmap_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  swap_reserve_by_cred (scalar_t__,int /*<<< orphan*/ ) ; 
 struct vmspace* vmspace_fork (struct vmspace*,scalar_t__*) ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 

int
vmspace_unshare(struct proc *p)
{
	struct vmspace *oldvmspace = p->p_vmspace;
	struct vmspace *newvmspace;
	vm_ooffset_t fork_charge;

	if (oldvmspace->vm_refcnt == 1)
		return (0);
	fork_charge = 0;
	newvmspace = vmspace_fork(oldvmspace, &fork_charge);
	if (newvmspace == NULL)
		return (ENOMEM);
	if (!swap_reserve_by_cred(fork_charge, p->p_ucred)) {
		vmspace_free(newvmspace);
		return (ENOMEM);
	}
	PROC_VMSPACE_LOCK(p);
	p->p_vmspace = newvmspace;
	PROC_VMSPACE_UNLOCK(p);
	if (p == curthread->td_proc)
		pmap_activate(curthread);
	vmspace_free(oldvmspace);
	return (0);
}