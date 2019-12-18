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
struct vmspace {int vm_refcnt; } ;
struct thread {struct proc* td_proc; } ;
struct proc {struct vmspace* p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_VMSPACE_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_VMSPACE_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  atomic_add_int (int*,int) ; 
 int /*<<< orphan*/  atomic_fcmpset_int (int*,int*,int) ; 
 int /*<<< orphan*/  pmap_activate (struct thread*) ; 
 int /*<<< orphan*/  pmap_remove_pages (int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 struct vmspace vmspace0 ; 
 int /*<<< orphan*/  vmspace_container_reset (struct proc*) ; 
 int /*<<< orphan*/  vmspace_dofree (struct vmspace*) ; 
 int /*<<< orphan*/  vmspace_pmap (struct vmspace*) ; 

void
vmspace_exit(struct thread *td)
{
	int refcnt;
	struct vmspace *vm;
	struct proc *p;

	/*
	 * Release user portion of address space.
	 * This releases references to vnodes,
	 * which could cause I/O if the file has been unlinked.
	 * Need to do this early enough that we can still sleep.
	 *
	 * The last exiting process to reach this point releases as
	 * much of the environment as it can. vmspace_dofree() is the
	 * slower fallback in case another process had a temporary
	 * reference to the vmspace.
	 */

	p = td->td_proc;
	vm = p->p_vmspace;
	atomic_add_int(&vmspace0.vm_refcnt, 1);
	refcnt = vm->vm_refcnt;
	do {
		if (refcnt > 1 && p->p_vmspace != &vmspace0) {
			/* Switch now since other proc might free vmspace */
			PROC_VMSPACE_LOCK(p);
			p->p_vmspace = &vmspace0;
			PROC_VMSPACE_UNLOCK(p);
			pmap_activate(td);
		}
	} while (!atomic_fcmpset_int(&vm->vm_refcnt, &refcnt, refcnt - 1));
	if (refcnt == 1) {
		if (p->p_vmspace != vm) {
			/* vmspace not yet freed, switch back */
			PROC_VMSPACE_LOCK(p);
			p->p_vmspace = vm;
			PROC_VMSPACE_UNLOCK(p);
			pmap_activate(td);
		}
		pmap_remove_pages(vmspace_pmap(vm));
		/* Switch now since this proc will free vmspace */
		PROC_VMSPACE_LOCK(p);
		p->p_vmspace = &vmspace0;
		PROC_VMSPACE_UNLOCK(p);
		pmap_activate(td);
		vmspace_dofree(vm);
	}
#ifdef RACCT
	if (racct_enable)
		vmspace_container_reset(p);
#endif
}