#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct thread {struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_vmspace; } ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_7__ {TYPE_1__* pm_asid; struct TYPE_7__* pm_segtab; int /*<<< orphan*/  pm_active; } ;
struct TYPE_6__ {int /*<<< orphan*/  asid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR_ATOMIC (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (size_t,int /*<<< orphan*/ *) ; 
 void* PCPU_GET (size_t) ; 
 int /*<<< orphan*/  PCPU_SET (size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 size_t curpmap ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mips_wr_entryhi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_asid_alloc (TYPE_2__*) ; 
 size_t segbase ; 
 TYPE_2__* vmspace_pmap (int /*<<< orphan*/ ) ; 

void
pmap_activate(struct thread *td)
{
	pmap_t pmap, oldpmap;
	struct proc *p = td->td_proc;
	u_int cpuid;

	critical_enter();

	pmap = vmspace_pmap(p->p_vmspace);
	oldpmap = PCPU_GET(curpmap);
	cpuid = PCPU_GET(cpuid);

	if (oldpmap)
		CPU_CLR_ATOMIC(cpuid, &oldpmap->pm_active);
	CPU_SET_ATOMIC(cpuid, &pmap->pm_active);
	pmap_asid_alloc(pmap);
	if (td == curthread) {
		PCPU_SET(segbase, pmap->pm_segtab);
		mips_wr_entryhi(pmap->pm_asid[cpuid].asid);
	}

	PCPU_SET(curpmap, pmap);
	critical_exit();
}