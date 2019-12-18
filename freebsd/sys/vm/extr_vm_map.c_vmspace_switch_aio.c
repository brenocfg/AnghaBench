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
struct vmspace {scalar_t__ vm_refcnt; } ;
struct TYPE_2__ {struct vmspace* p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  atomic_add_int (scalar_t__*,int) ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  pmap_activate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 

void
vmspace_switch_aio(struct vmspace *newvm)
{
	struct vmspace *oldvm;

	/* XXX: Need some way to assert that this is an aio daemon. */

	KASSERT(newvm->vm_refcnt > 0,
	    ("vmspace_switch_aio: newvm unreferenced"));

	oldvm = curproc->p_vmspace;
	if (oldvm == newvm)
		return;

	/*
	 * Point to the new address space and refer to it.
	 */
	curproc->p_vmspace = newvm;
	atomic_add_int(&newvm->vm_refcnt, 1);

	/* Activate the new mapping. */
	pmap_activate(curthread);

	vmspace_free(oldvm);
}