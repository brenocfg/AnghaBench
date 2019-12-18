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
struct vmspace {int dummy; } ;
struct proc {struct vmspace* p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PROC_VMSPACE_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_VMSPACE_UNLOCK (struct proc*) ; 
 struct vmspace vmspace0 ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 

void
vmspace_exitfree(struct proc *p)
{
	struct vmspace *vm;

	PROC_VMSPACE_LOCK(p);
	vm = p->p_vmspace;
	p->p_vmspace = NULL;
	PROC_VMSPACE_UNLOCK(p);
	KASSERT(vm == &vmspace0, ("vmspace_exitfree: wrong vmspace"));
	vmspace_free(vm);
}