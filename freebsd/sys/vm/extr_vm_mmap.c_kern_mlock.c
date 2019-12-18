#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_map_t ;
struct ucred {int dummy; } ;
struct proc {TYPE_1__* p_vmspace; } ;
struct TYPE_5__ {int /*<<< orphan*/  pmap; } ;
struct TYPE_4__ {TYPE_2__ vm_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  PRIV_VM_MLOCK ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  RACCT_MEMLOCK ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int VM_MAP_WIRE_NOHOLES ; 
 int VM_MAP_WIRE_USER ; 
 scalar_t__ atop (scalar_t__) ; 
 unsigned long lim_cur_proc (struct proc*,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_wired_count (int /*<<< orphan*/ ) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 unsigned long ptoa (scalar_t__) ; 
 scalar_t__ racct_enable ; 
 int racct_set (struct proc*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int vm_map_wire (TYPE_2__*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ vm_page_max_user_wired ; 

int
kern_mlock(struct proc *proc, struct ucred *cred, uintptr_t addr0, size_t len)
{
	vm_offset_t addr, end, last, start;
	vm_size_t npages, size;
	vm_map_t map;
	unsigned long nsize;
	int error;

	error = priv_check_cred(cred, PRIV_VM_MLOCK);
	if (error)
		return (error);
	addr = addr0;
	size = len;
	last = addr + size;
	start = trunc_page(addr);
	end = round_page(last);
	if (last < addr || end < addr)
		return (EINVAL);
	npages = atop(end - start);
	if (npages > vm_page_max_user_wired)
		return (ENOMEM);
	map = &proc->p_vmspace->vm_map;
	PROC_LOCK(proc);
	nsize = ptoa(npages + pmap_wired_count(map->pmap));
	if (nsize > lim_cur_proc(proc, RLIMIT_MEMLOCK)) {
		PROC_UNLOCK(proc);
		return (ENOMEM);
	}
	PROC_UNLOCK(proc);
#ifdef RACCT
	if (racct_enable) {
		PROC_LOCK(proc);
		error = racct_set(proc, RACCT_MEMLOCK, nsize);
		PROC_UNLOCK(proc);
		if (error != 0)
			return (ENOMEM);
	}
#endif
	error = vm_map_wire(map, start, end,
	    VM_MAP_WIRE_USER | VM_MAP_WIRE_NOHOLES);
#ifdef RACCT
	if (racct_enable && error != KERN_SUCCESS) {
		PROC_LOCK(proc);
		racct_set(proc, RACCT_MEMLOCK,
		    ptoa(pmap_wired_count(map->pmap)));
		PROC_UNLOCK(proc);
	}
#endif
	return (error == KERN_SUCCESS ? 0 : ENOMEM);
}