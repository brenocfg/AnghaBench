#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
struct thread {TYPE_2__* td_proc; } ;
struct TYPE_4__ {TYPE_1__* p_vmspace; int /*<<< orphan*/  p_pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int MADV_PROTECT ; 
 int PPROT_SET ; 
 int /*<<< orphan*/  PROC_SPROTECT ; 
 int /*<<< orphan*/  P_PID ; 
 int kern_procctl (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 size_t round_page (size_t) ; 
 size_t trunc_page (size_t) ; 
 int vm_map_madvise (int /*<<< orphan*/ *,size_t,size_t,int) ; 
 size_t vm_map_max (int /*<<< orphan*/ *) ; 
 size_t vm_map_min (int /*<<< orphan*/ *) ; 

int
kern_madvise(struct thread *td, uintptr_t addr0, size_t len, int behav)
{
	vm_map_t map;
	vm_offset_t addr, end, start;
	int flags;

	/*
	 * Check for our special case, advising the swap pager we are
	 * "immortal."
	 */
	if (behav == MADV_PROTECT) {
		flags = PPROT_SET;
		return (kern_procctl(td, P_PID, td->td_proc->p_pid,
		    PROC_SPROTECT, &flags));
	}

	/*
	 * Check for illegal addresses.  Watch out for address wrap... Note
	 * that VM_*_ADDRESS are not constants due to casts (argh).
	 */
	map = &td->td_proc->p_vmspace->vm_map;
	addr = addr0;
	if (addr < vm_map_min(map) || addr + len > vm_map_max(map))
		return (EINVAL);
	if ((addr + len) < addr)
		return (EINVAL);

	/*
	 * Since this routine is only advisory, we default to conservative
	 * behavior.
	 */
	start = trunc_page(addr);
	end = round_page(addr + len);

	/*
	 * vm_map_madvise() checks for illegal values of behav.
	 */
	return (vm_map_madvise(map, start, end, behav));
}