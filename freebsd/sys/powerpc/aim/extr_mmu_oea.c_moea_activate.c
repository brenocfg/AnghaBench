#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_pcb; TYPE_3__* td_proc; } ;
typedef  TYPE_6__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_13__ {int /*<<< orphan*/  pm_active; struct TYPE_13__* pmap_phys; } ;
struct TYPE_12__ {int /*<<< orphan*/  usr_vsid; } ;
struct TYPE_11__ {TYPE_5__ aim; } ;
struct TYPE_10__ {TYPE_2__* p_vmspace; } ;
struct TYPE_9__ {TYPE_6__ vm_pmap; } ;
struct TYPE_8__ {TYPE_4__ pcb_cpu; } ;

/* Variables and functions */
 int ADDR_SR_SHFT ; 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int USER_SR ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  curpmap ; 
 int /*<<< orphan*/  mtsrin (int,int /*<<< orphan*/ ) ; 

void
moea_activate(mmu_t mmu, struct thread *td)
{
	pmap_t	pm, pmr;

	/*
	 * Load all the data we need up front to encourage the compiler to
	 * not issue any loads while we have interrupts disabled below.
	 */
	pm = &td->td_proc->p_vmspace->vm_pmap;
	pmr = pm->pmap_phys;

	CPU_SET(PCPU_GET(cpuid), &pm->pm_active);
	PCPU_SET(curpmap, pmr);

	mtsrin(USER_SR << ADDR_SR_SHFT, td->td_pcb->pcb_cpu.aim.usr_vsid);
}