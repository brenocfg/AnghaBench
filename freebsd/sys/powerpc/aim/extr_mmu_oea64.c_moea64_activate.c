#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_3__* td_pcb; TYPE_5__* td_proc; } ;
typedef  TYPE_6__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_14__ {int /*<<< orphan*/  userslb; } ;
struct TYPE_13__ {int /*<<< orphan*/  pmap_phys; int /*<<< orphan*/  pm_slb; int /*<<< orphan*/  pm_active; } ;
struct TYPE_12__ {TYPE_4__* p_vmspace; } ;
struct TYPE_11__ {TYPE_6__ vm_pmap; } ;
struct TYPE_8__ {int /*<<< orphan*/  usr_vsid; } ;
struct TYPE_9__ {TYPE_1__ aim; } ;
struct TYPE_10__ {TYPE_2__ pcb_cpu; } ;

/* Variables and functions */
 int ADDR_SR_SHFT ; 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USER_SR ; 
 TYPE_7__ aim ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  curpmap ; 
 int /*<<< orphan*/  mtsrin (int,int /*<<< orphan*/ ) ; 

void
moea64_activate(mmu_t mmu, struct thread *td)
{
	pmap_t	pm;

	pm = &td->td_proc->p_vmspace->vm_pmap;
	CPU_SET(PCPU_GET(cpuid), &pm->pm_active);

	#ifdef __powerpc64__
	PCPU_SET(aim.userslb, pm->pm_slb);
	__asm __volatile("slbmte %0, %1; isync" ::
	    "r"(td->td_pcb->pcb_cpu.aim.usr_vsid), "r"(USER_SLB_SLBE));
	#else
	PCPU_SET(curpmap, pm->pmap_phys);
	mtsrin(USER_SR << ADDR_SR_SHFT, td->td_pcb->pcb_cpu.aim.usr_vsid);
	#endif
}