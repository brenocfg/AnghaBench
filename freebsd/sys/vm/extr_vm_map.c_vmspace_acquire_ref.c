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
struct proc {struct vmspace* p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_VMSPACE_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_VMSPACE_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  atomic_fcmpset_int (int*,int*,int) ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 

struct vmspace *
vmspace_acquire_ref(struct proc *p)
{
	struct vmspace *vm;
	int refcnt;

	PROC_VMSPACE_LOCK(p);
	vm = p->p_vmspace;
	if (vm == NULL) {
		PROC_VMSPACE_UNLOCK(p);
		return (NULL);
	}
	refcnt = vm->vm_refcnt;
	do {
		if (refcnt <= 0) { 	/* Avoid 0->1 transition */
			PROC_VMSPACE_UNLOCK(p);
			return (NULL);
		}
	} while (!atomic_fcmpset_int(&vm->vm_refcnt, &refcnt, refcnt + 1));
	if (vm != p->p_vmspace) {
		PROC_VMSPACE_UNLOCK(p);
		vmspace_free(vm);
		return (NULL);
	}
	PROC_VMSPACE_UNLOCK(p);
	return (vm);
}