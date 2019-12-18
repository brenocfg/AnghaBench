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
typedef  void* u_int ;
struct thread {TYPE_1__* td_proc; } ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_6__ {int /*<<< orphan*/  pm_active; int /*<<< orphan*/  pm_satp; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_CLR_ATOMIC (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (void*,int /*<<< orphan*/ *) ; 
 void* PCPU_GET (void*) ; 
 int /*<<< orphan*/  PCPU_SET (void*,TYPE_2__*) ; 
 void* curpmap ; 
 int /*<<< orphan*/  load_satp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfence_vma () ; 
 TYPE_2__* vmspace_pmap (int /*<<< orphan*/ ) ; 

void
pmap_activate_sw(struct thread *td)
{
	pmap_t oldpmap, pmap;
	u_int hart;

	oldpmap = PCPU_GET(curpmap);
	pmap = vmspace_pmap(td->td_proc->p_vmspace);
	if (pmap == oldpmap)
		return;
	load_satp(pmap->pm_satp);

	hart = PCPU_GET(hart);
#ifdef SMP
	CPU_SET_ATOMIC(hart, &pmap->pm_active);
	CPU_CLR_ATOMIC(hart, &oldpmap->pm_active);
#else
	CPU_SET(hart, &pmap->pm_active);
	CPU_CLR(hart, &oldpmap->pm_active);
#endif
	PCPU_SET(curpmap, pmap);

	sfence_vma();
}