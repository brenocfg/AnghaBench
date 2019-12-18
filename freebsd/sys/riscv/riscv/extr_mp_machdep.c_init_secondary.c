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
typedef  size_t uint64_t ;
typedef  size_t u_int ;
struct pcpu {TYPE_1__* pc_idlethread; int /*<<< orphan*/  pc_curpcb; TYPE_1__* pc_curthread; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_vmspace; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIE_SEIE ; 
 int /*<<< orphan*/  SIE_SSIE ; 
 struct pcpu* __pcpu ; 
 int /*<<< orphan*/  ap_boot_mtx ; 
 int /*<<< orphan*/  aps_ready ; 
 int /*<<< orphan*/  atomic_add_rel_32 (scalar_t__*,int) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int) ; 
 size_t boot_hart ; 
 int /*<<< orphan*/  cpu_initclocks_ap () ; 
 int /*<<< orphan*/  csr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identify_cpu () ; 
 int /*<<< orphan*/  idlethread ; 
 scalar_t__ mp_maxid ; 
 scalar_t__ mp_ncpus ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_activate_boot (int /*<<< orphan*/ ) ; 
 TYPE_2__ proc0 ; 
 int /*<<< orphan*/  riscv_unmask_ipi () ; 
 int /*<<< orphan*/  sched_throw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sie ; 
 int /*<<< orphan*/  sip ; 
 scalar_t__ smp_cpus ; 
 int /*<<< orphan*/  smp_started ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ ) ; 

void
init_secondary(uint64_t hart)
{
	struct pcpu *pcpup;
	u_int cpuid;

	/* Renumber this cpu */
	cpuid = hart;
	if (cpuid < boot_hart)
		cpuid += mp_maxid + 1;
	cpuid -= boot_hart;

	/* Setup the pcpu pointer */
	pcpup = &__pcpu[cpuid];
	__asm __volatile("mv tp, %0" :: "r"(pcpup));

	/* Workaround: make sure wfi doesn't halt the hart */
	csr_set(sie, SIE_SSIE);
	csr_set(sip, SIE_SSIE);

	/* Spin until the BSP releases the APs */
	while (!aps_ready)
		__asm __volatile("wfi");

	/* Initialize curthread */
	KASSERT(PCPU_GET(idlethread) != NULL, ("no idle thread"));
	pcpup->pc_curthread = pcpup->pc_idlethread;
	pcpup->pc_curpcb = pcpup->pc_idlethread->td_pcb;

	/*
	 * Identify current CPU. This is necessary to setup
	 * affinity registers and to provide support for
	 * runtime chip identification.
	 */
	identify_cpu();

	/* Enable software interrupts */
	riscv_unmask_ipi();

#ifndef EARLY_AP_STARTUP
	/* Start per-CPU event timers. */
	cpu_initclocks_ap();
#endif

	/* Enable external (PLIC) interrupts */
	csr_set(sie, SIE_SEIE);

	/* Activate process 0's pmap. */
	pmap_activate_boot(vmspace_pmap(proc0.p_vmspace));

	mtx_lock_spin(&ap_boot_mtx);

	atomic_add_rel_32(&smp_cpus, 1);

	if (smp_cpus == mp_ncpus) {
		/* enable IPI's, tlb shootdown, freezes etc */
		atomic_store_rel_int(&smp_started, 1);
	}

	mtx_unlock_spin(&ap_boot_mtx);

	/* Enter the scheduler */
	sched_throw(NULL);

	panic("scheduler returned us to init_secondary");
	/* NOTREACHED */
}