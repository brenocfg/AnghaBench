#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct pcpu {int /*<<< orphan*/  pc_curpmap; TYPE_1__* pc_idlethread; int /*<<< orphan*/  pc_curpcb; TYPE_1__* pc_curthread; } ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_2__ {int /*<<< orphan*/  td_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/ * PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 struct pcpu* __pcpu ; 
 int /*<<< orphan*/  ap_boot_mtx ; 
 int /*<<< orphan*/  aps_ready ; 
 int /*<<< orphan*/  atomic_add_rel_32 (scalar_t__*,int) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_initclocks_ap () ; 
 int /*<<< orphan*/  dbg_init () ; 
 int /*<<< orphan*/  identify_cpu () ; 
 int /*<<< orphan*/  idlethread ; 
 int /*<<< orphan*/  install_cpu_errata () ; 
 int /*<<< orphan*/  intr_enable () ; 
 int /*<<< orphan*/  intr_pic_init_secondary () ; 
 scalar_t__ mp_ncpus ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pan_enable () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pmap_to_ttbr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_throw (int /*<<< orphan*/ *) ; 
 scalar_t__ smp_cpus ; 
 int /*<<< orphan*/  smp_started ; 
 int /*<<< orphan*/  ttbr0_el1 ; 
 int /*<<< orphan*/  vfp_init () ; 
 int /*<<< orphan*/  vmspace0 ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ *) ; 

void
init_secondary(uint64_t cpu)
{
	struct pcpu *pcpup;
	pmap_t pmap0;

	pcpup = &__pcpu[cpu];
	/*
	 * Set the pcpu pointer with a backup in tpidr_el1 to be
	 * loaded when entering the kernel from userland.
	 */
	__asm __volatile(
	    "mov x18, %0 \n"
	    "msr tpidr_el1, %0" :: "r"(pcpup));

	/* Spin until the BSP releases the APs */
	while (!aps_ready)
		__asm __volatile("wfe");

	/* Initialize curthread */
	KASSERT(PCPU_GET(idlethread) != NULL, ("no idle thread"));
	pcpup->pc_curthread = pcpup->pc_idlethread;
	pcpup->pc_curpcb = pcpup->pc_idlethread->td_pcb;

	/* Initialize curpmap to match TTBR0's current setting. */
	pmap0 = vmspace_pmap(&vmspace0);
	KASSERT(pmap_to_ttbr0(pmap0) == READ_SPECIALREG(ttbr0_el1),
	    ("pmap0 doesn't match cpu %ld's ttbr0", cpu));
	pcpup->pc_curpmap = pmap0;

	/*
	 * Identify current CPU. This is necessary to setup
	 * affinity registers and to provide support for
	 * runtime chip identification.
	 */
	identify_cpu();
	install_cpu_errata();

	intr_pic_init_secondary();

	/* Start per-CPU event timers. */
	cpu_initclocks_ap();

#ifdef VFP
	vfp_init();
#endif

	dbg_init();
	pan_enable();

	/* Enable interrupts */
	intr_enable();

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