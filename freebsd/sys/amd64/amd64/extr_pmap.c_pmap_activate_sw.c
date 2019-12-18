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
struct TYPE_6__ {int /*<<< orphan*/  pm_active; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_CLR_ATOMIC (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_VENDOR_INTEL ; 
 void* PCPU_GET (void*) ; 
 scalar_t__ cpu_vendor_id ; 
 void* curpmap ; 
 int /*<<< orphan*/  mfence () ; 
 int /*<<< orphan*/  pmap_activate_sw_mode (struct thread*,TYPE_2__*,void*) ; 
 TYPE_2__* vmspace_pmap (int /*<<< orphan*/ ) ; 

void
pmap_activate_sw(struct thread *td)
{
	pmap_t oldpmap, pmap;
	u_int cpuid;

	oldpmap = PCPU_GET(curpmap);
	pmap = vmspace_pmap(td->td_proc->p_vmspace);
	if (oldpmap == pmap) {
		if (cpu_vendor_id != CPU_VENDOR_INTEL)
			mfence();
		return;
	}
	cpuid = PCPU_GET(cpuid);
#ifdef SMP
	CPU_SET_ATOMIC(cpuid, &pmap->pm_active);
#else
	CPU_SET(cpuid, &pmap->pm_active);
#endif
	pmap_activate_sw_mode(td, pmap, cpuid);
#ifdef SMP
	CPU_CLR_ATOMIC(cpuid, &oldpmap->pm_active);
#else
	CPU_CLR(cpuid, &oldpmap->pm_active);
#endif
}