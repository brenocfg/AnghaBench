#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmspace {int vm_refcnt; scalar_t__ vm_shm; } ;
struct TYPE_2__ {struct domainset* dr_policy; } ;
struct thread {TYPE_1__ td_domain; struct proc* td_proc; } ;
struct proc {struct vmspace* p_vmspace; } ;
struct domainset {int /*<<< orphan*/  ds_mask; } ;

/* Variables and functions */
 int RFMEM ; 
 int RFPROC ; 
 int /*<<< orphan*/  atomic_add_int (int*,int) ; 
 int /*<<< orphan*/  cpu_fork (struct thread*,struct proc*,struct thread*,int) ; 
 int /*<<< orphan*/  shmfork (struct proc*,struct proc*) ; 
 scalar_t__ vm_page_count_severe_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_wait_doms (int /*<<< orphan*/ *) ; 
 int vmspace_unshare (struct proc*) ; 

int
vm_forkproc(struct thread *td, struct proc *p2, struct thread *td2,
    struct vmspace *vm2, int flags)
{
	struct proc *p1 = td->td_proc;
	struct domainset *dset;
	int error;

	if ((flags & RFPROC) == 0) {
		/*
		 * Divorce the memory, if it is shared, essentially
		 * this changes shared memory amongst threads, into
		 * COW locally.
		 */
		if ((flags & RFMEM) == 0) {
			if (p1->p_vmspace->vm_refcnt > 1) {
				error = vmspace_unshare(p1);
				if (error)
					return (error);
			}
		}
		cpu_fork(td, p2, td2, flags);
		return (0);
	}

	if (flags & RFMEM) {
		p2->p_vmspace = p1->p_vmspace;
		atomic_add_int(&p1->p_vmspace->vm_refcnt, 1);
	}
	dset = td2->td_domain.dr_policy;
	while (vm_page_count_severe_set(&dset->ds_mask)) {
		vm_wait_doms(&dset->ds_mask);
	}

	if ((flags & RFMEM) == 0) {
		p2->p_vmspace = vm2;
		if (p1->p_vmspace->vm_shm)
			shmfork(p1, p2);
	}

	/*
	 * cpu_fork will copy and update the pcb, set up the kernel stack,
	 * and make the child ready to run.
	 */
	cpu_fork(td, p2, td2, flags);
	return (0);
}