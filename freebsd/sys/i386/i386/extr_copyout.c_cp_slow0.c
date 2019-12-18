#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct pcpu {int /*<<< orphan*/  pc_copyout_mlock; int /*<<< orphan*/  pc_copyout_slock; scalar_t__ pc_copyout_saddr; scalar_t__ pc_copyout_maddr; } ;
struct TYPE_6__ {TYPE_1__* p_vmspace; } ;
struct TYPE_5__ {scalar_t__ td_vslock_sz; int td_pflags; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int TDP_NOFAULTING ; 
 int /*<<< orphan*/  THREAD_CAN_SLEEP () ; 
 int VM_PROT_QUICK_NOFAULT ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 TYPE_3__* curproc ; 
 TYPE_2__* curthread ; 
 struct pcpu* get_pcpu () ; 
 int howmany (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_cp_slow0_map (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int vm_fault_quick_hold_pages (int /*<<< orphan*/ *,scalar_t__,size_t,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_page_unhold_pages (int /*<<< orphan*/ *,int) ; 

int
cp_slow0(vm_offset_t uva, size_t len, bool write,
    void (*f)(vm_offset_t, void *), void *arg)
{
	struct pcpu *pc;
	vm_page_t m[2];
	vm_offset_t kaddr;
	int error, i, plen;
	bool sleepable;

	plen = howmany(uva - trunc_page(uva) + len, PAGE_SIZE);
	MPASS(plen <= nitems(m));
	error = 0;
	i = vm_fault_quick_hold_pages(&curproc->p_vmspace->vm_map, uva, len,
	    (write ? VM_PROT_WRITE : VM_PROT_READ) | VM_PROT_QUICK_NOFAULT,
	    m, nitems(m));
	if (i != plen)
		return (EFAULT);
	sched_pin();
	pc = get_pcpu();
	if (!THREAD_CAN_SLEEP() || curthread->td_vslock_sz > 0 ||
	    (curthread->td_pflags & TDP_NOFAULTING) != 0) {
		sleepable = false;
		mtx_lock(&pc->pc_copyout_mlock);
		kaddr = pc->pc_copyout_maddr;
	} else {
		sleepable = true;
		sx_xlock(&pc->pc_copyout_slock);
		kaddr = pc->pc_copyout_saddr;
	}
	pmap_cp_slow0_map(kaddr, plen, m);
	kaddr += uva - trunc_page(uva);
	f(kaddr, arg);
	sched_unpin();
	if (sleepable)
		sx_xunlock(&pc->pc_copyout_slock);
	else
		mtx_unlock(&pc->pc_copyout_mlock);
	vm_page_unhold_pages(m, plen);
	return (error);
}