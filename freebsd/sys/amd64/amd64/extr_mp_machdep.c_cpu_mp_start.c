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
struct TYPE_4__ {int cpu_bsp; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* start_all_aps ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IDTVEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPI_BITMAP_VECTOR ; 
 int /*<<< orphan*/  IPI_INVLCACHE ; 
 int /*<<< orphan*/  IPI_INVLPG ; 
 int /*<<< orphan*/  IPI_INVLRNG ; 
 int /*<<< orphan*/  IPI_INVLTLB ; 
 int /*<<< orphan*/  IPI_RENDEZVOUS ; 
 int /*<<< orphan*/  IPI_STOP ; 
 int /*<<< orphan*/  IPI_SUSPEND ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAXCPU ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDT_SYSIGT ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  apic_id ; 
 int /*<<< orphan*/  assign_cpu_ids () ; 
 int boot_cpu_id ; 
 int* cpu_apic_ids ; 
 TYPE_2__* cpu_info ; 
 int /*<<< orphan*/  cpustop ; 
 int /*<<< orphan*/  cpustop_pti ; 
 int /*<<< orphan*/  cpususpend ; 
 int /*<<< orphan*/  cpususpend_pti ; 
 TYPE_1__ init_ops ; 
 int /*<<< orphan*/  invlcache ; 
 int /*<<< orphan*/  invlcache_pti ; 
 int /*<<< orphan*/  invlpg ; 
 int /*<<< orphan*/  invlpg_invpcid ; 
 int /*<<< orphan*/  invlpg_invpcid_pti ; 
 int /*<<< orphan*/  invlpg_pcid ; 
 int /*<<< orphan*/  invlpg_pcid_pti ; 
 int /*<<< orphan*/  invlpg_pti ; 
 int /*<<< orphan*/  invlrng ; 
 int /*<<< orphan*/  invlrng_invpcid ; 
 int /*<<< orphan*/  invlrng_invpcid_pti ; 
 int /*<<< orphan*/  invlrng_pcid ; 
 int /*<<< orphan*/  invlrng_pcid_pti ; 
 int /*<<< orphan*/  invlrng_pti ; 
 int /*<<< orphan*/  invltlb ; 
 int /*<<< orphan*/  invltlb_invpcid_nopti ; 
 int /*<<< orphan*/  invltlb_invpcid_pti_pti ; 
 int /*<<< orphan*/  invltlb_pcid ; 
 int /*<<< orphan*/  invltlb_pcid_pti ; 
 int /*<<< orphan*/  invltlb_pti ; 
 scalar_t__ invpcid_works ; 
 int /*<<< orphan*/  ipi_intr_bitmap_handler ; 
 int /*<<< orphan*/  ipi_intr_bitmap_handler_pti ; 
 scalar_t__ pmap_pcid_enabled ; 
 scalar_t__ pti ; 
 int /*<<< orphan*/  rendezvous ; 
 int /*<<< orphan*/  rendezvous_pti ; 
 int /*<<< orphan*/  set_interrupt_apic_ids () ; 
 int /*<<< orphan*/  setidt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  topo_probe () ; 

void
cpu_mp_start(void)
{
	int i;

	/* Initialize the logical ID to APIC ID table. */
	for (i = 0; i < MAXCPU; i++) {
		cpu_apic_ids[i] = -1;
	}

	/* Install an inter-CPU IPI for TLB invalidation */
	if (pmap_pcid_enabled) {
		if (invpcid_works) {
			setidt(IPI_INVLTLB, pti ?
			    IDTVEC(invltlb_invpcid_pti_pti) :
			    IDTVEC(invltlb_invpcid_nopti), SDT_SYSIGT,
			    SEL_KPL, 0);
			setidt(IPI_INVLPG, pti ? IDTVEC(invlpg_invpcid_pti) :
			    IDTVEC(invlpg_invpcid), SDT_SYSIGT, SEL_KPL, 0);
			setidt(IPI_INVLRNG, pti ? IDTVEC(invlrng_invpcid_pti) :
			    IDTVEC(invlrng_invpcid), SDT_SYSIGT, SEL_KPL, 0);
		} else {
			setidt(IPI_INVLTLB, pti ? IDTVEC(invltlb_pcid_pti) :
			    IDTVEC(invltlb_pcid), SDT_SYSIGT, SEL_KPL, 0);
			setidt(IPI_INVLPG, pti ? IDTVEC(invlpg_pcid_pti) :
			    IDTVEC(invlpg_pcid), SDT_SYSIGT, SEL_KPL, 0);
			setidt(IPI_INVLRNG, pti ? IDTVEC(invlrng_pcid_pti) :
			    IDTVEC(invlrng_pcid), SDT_SYSIGT, SEL_KPL, 0);
		}
	} else {
		setidt(IPI_INVLTLB, pti ? IDTVEC(invltlb_pti) : IDTVEC(invltlb),
		    SDT_SYSIGT, SEL_KPL, 0);
		setidt(IPI_INVLPG, pti ? IDTVEC(invlpg_pti) : IDTVEC(invlpg),
		    SDT_SYSIGT, SEL_KPL, 0);
		setidt(IPI_INVLRNG, pti ? IDTVEC(invlrng_pti) : IDTVEC(invlrng),
		    SDT_SYSIGT, SEL_KPL, 0);
	}

	/* Install an inter-CPU IPI for cache invalidation. */
	setidt(IPI_INVLCACHE, pti ? IDTVEC(invlcache_pti) : IDTVEC(invlcache),
	    SDT_SYSIGT, SEL_KPL, 0);

	/* Install an inter-CPU IPI for all-CPU rendezvous */
	setidt(IPI_RENDEZVOUS, pti ? IDTVEC(rendezvous_pti) :
	    IDTVEC(rendezvous), SDT_SYSIGT, SEL_KPL, 0);

	/* Install generic inter-CPU IPI handler */
	setidt(IPI_BITMAP_VECTOR, pti ? IDTVEC(ipi_intr_bitmap_handler_pti) :
	    IDTVEC(ipi_intr_bitmap_handler), SDT_SYSIGT, SEL_KPL, 0);

	/* Install an inter-CPU IPI for CPU stop/restart */
	setidt(IPI_STOP, pti ? IDTVEC(cpustop_pti) : IDTVEC(cpustop),
	    SDT_SYSIGT, SEL_KPL, 0);

	/* Install an inter-CPU IPI for CPU suspend/resume */
	setidt(IPI_SUSPEND, pti ? IDTVEC(cpususpend_pti) : IDTVEC(cpususpend),
	    SDT_SYSIGT, SEL_KPL, 0);

	/* Set boot_cpu_id if needed. */
	if (boot_cpu_id == -1) {
		boot_cpu_id = PCPU_GET(apic_id);
		cpu_info[boot_cpu_id].cpu_bsp = 1;
	} else
		KASSERT(boot_cpu_id == PCPU_GET(apic_id),
		    ("BSP's APIC ID doesn't match boot_cpu_id"));

	/* Probe logical/physical core configuration. */
	topo_probe();

	assign_cpu_ids();

	/* Start each Application Processor */
	init_ops.start_all_aps();

	set_interrupt_apic_ids();
}