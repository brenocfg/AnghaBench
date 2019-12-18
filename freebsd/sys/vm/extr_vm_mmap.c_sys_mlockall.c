#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_map_t ;
struct thread {TYPE_9__* td_proc; } ;
struct mlockall_args {int how; } ;
struct TYPE_14__ {TYPE_1__* p_vmspace; } ;
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/  pmap; } ;
struct TYPE_12__ {TYPE_2__ vm_map; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  MAP_WIREFUTURE ; 
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 int /*<<< orphan*/  PRIV_VM_MLOCK ; 
 int /*<<< orphan*/  PROC_LOCK (TYPE_9__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_9__*) ; 
 int /*<<< orphan*/  RACCT_MEMLOCK ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int VM_MAP_WIRE_HOLESOK ; 
 int VM_MAP_WIRE_USER ; 
 scalar_t__ lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_mlock ; 
 int /*<<< orphan*/  pmap_wired_count (int /*<<< orphan*/ ) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 int racct_set (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_max (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_min (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_modflags (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_2__*) ; 
 int vm_map_wire (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
sys_mlockall(struct thread *td, struct mlockall_args *uap)
{
	vm_map_t map;
	int error;

	map = &td->td_proc->p_vmspace->vm_map;
	error = priv_check(td, PRIV_VM_MLOCK);
	if (error)
		return (error);

	if ((uap->how == 0) || ((uap->how & ~(MCL_CURRENT|MCL_FUTURE)) != 0))
		return (EINVAL);

	/*
	 * If wiring all pages in the process would cause it to exceed
	 * a hard resource limit, return ENOMEM.
	 */
	if (!old_mlock && uap->how & MCL_CURRENT) {
		if (map->size > lim_cur(td, RLIMIT_MEMLOCK))
			return (ENOMEM);
	}
#ifdef RACCT
	if (racct_enable) {
		PROC_LOCK(td->td_proc);
		error = racct_set(td->td_proc, RACCT_MEMLOCK, map->size);
		PROC_UNLOCK(td->td_proc);
		if (error != 0)
			return (ENOMEM);
	}
#endif

	if (uap->how & MCL_FUTURE) {
		vm_map_lock(map);
		vm_map_modflags(map, MAP_WIREFUTURE, 0);
		vm_map_unlock(map);
		error = 0;
	}

	if (uap->how & MCL_CURRENT) {
		/*
		 * P1003.1-2001 mandates that all currently mapped pages
		 * will be memory resident and locked (wired) upon return
		 * from mlockall(). vm_map_wire() will wire pages, by
		 * calling vm_fault_wire() for each page in the region.
		 */
		error = vm_map_wire(map, vm_map_min(map), vm_map_max(map),
		    VM_MAP_WIRE_USER|VM_MAP_WIRE_HOLESOK);
		if (error == KERN_SUCCESS)
			error = 0;
		else if (error == KERN_RESOURCE_SHORTAGE)
			error = ENOMEM;
		else
			error = EAGAIN;
	}
#ifdef RACCT
	if (racct_enable && error != KERN_SUCCESS) {
		PROC_LOCK(td->td_proc);
		racct_set(td->td_proc, RACCT_MEMLOCK,
		    ptoa(pmap_wired_count(map->pmap)));
		PROC_UNLOCK(td->td_proc);
	}
#endif

	return (error);
}