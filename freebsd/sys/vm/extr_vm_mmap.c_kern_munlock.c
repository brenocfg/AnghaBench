#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_offset_t ;
typedef  TYPE_2__* vm_map_t ;
struct thread {TYPE_4__* td_proc; } ;
struct TYPE_9__ {TYPE_1__* p_vmspace; } ;
struct TYPE_8__ {int /*<<< orphan*/  pmap; } ;
struct TYPE_7__ {TYPE_2__ vm_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  PRIV_VM_MUNLOCK ; 
 int /*<<< orphan*/  PROC_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  RACCT_MEMLOCK ; 
 int VM_MAP_WIRE_NOHOLES ; 
 int VM_MAP_WIRE_USER ; 
 int /*<<< orphan*/  pmap_wired_count (int /*<<< orphan*/ ) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  racct_set (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t round_page (size_t) ; 
 size_t trunc_page (size_t) ; 
 int vm_map_unwire (TYPE_2__*,size_t,size_t,int) ; 

int
kern_munlock(struct thread *td, uintptr_t addr0, size_t size)
{
	vm_offset_t addr, end, last, start;
#ifdef RACCT
	vm_map_t map;
#endif
	int error;

	error = priv_check(td, PRIV_VM_MUNLOCK);
	if (error)
		return (error);
	addr = addr0;
	last = addr + size;
	start = trunc_page(addr);
	end = round_page(last);
	if (last < addr || end < addr)
		return (EINVAL);
	error = vm_map_unwire(&td->td_proc->p_vmspace->vm_map, start, end,
	    VM_MAP_WIRE_USER | VM_MAP_WIRE_NOHOLES);
#ifdef RACCT
	if (racct_enable && error == KERN_SUCCESS) {
		PROC_LOCK(td->td_proc);
		map = &td->td_proc->p_vmspace->vm_map;
		racct_set(td->td_proc, RACCT_MEMLOCK,
		    ptoa(pmap_wired_count(map->pmap)));
		PROC_UNLOCK(td->td_proc);
	}
#endif
	return (error == KERN_SUCCESS ? 0 : ENOMEM);
}