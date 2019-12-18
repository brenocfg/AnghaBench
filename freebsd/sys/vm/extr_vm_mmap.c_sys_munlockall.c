#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_map_t ;
struct thread {TYPE_2__* td_proc; } ;
struct munlockall_args {int dummy; } ;
struct TYPE_6__ {TYPE_1__* p_vmspace; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  MAP_WIREFUTURE ; 
 int /*<<< orphan*/  PRIV_VM_MUNLOCK ; 
 int /*<<< orphan*/  PROC_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  RACCT_MEMLOCK ; 
 int VM_MAP_WIRE_HOLESOK ; 
 int VM_MAP_WIRE_USER ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  racct_set (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_max (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_min (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_modflags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ *) ; 
 int vm_map_unwire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
sys_munlockall(struct thread *td, struct munlockall_args *uap)
{
	vm_map_t map;
	int error;

	map = &td->td_proc->p_vmspace->vm_map;
	error = priv_check(td, PRIV_VM_MUNLOCK);
	if (error)
		return (error);

	/* Clear the MAP_WIREFUTURE flag from this vm_map. */
	vm_map_lock(map);
	vm_map_modflags(map, 0, MAP_WIREFUTURE);
	vm_map_unlock(map);

	/* Forcibly unwire all pages. */
	error = vm_map_unwire(map, vm_map_min(map), vm_map_max(map),
	    VM_MAP_WIRE_USER|VM_MAP_WIRE_HOLESOK);
#ifdef RACCT
	if (racct_enable && error == KERN_SUCCESS) {
		PROC_LOCK(td->td_proc);
		racct_set(td->td_proc, RACCT_MEMLOCK, 0);
		PROC_UNLOCK(td->td_proc);
	}
#endif

	return (error);
}