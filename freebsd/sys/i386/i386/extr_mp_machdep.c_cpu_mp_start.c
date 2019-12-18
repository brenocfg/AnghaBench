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
struct TYPE_2__ {int cpu_bsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCODE_SEL ; 
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  SDT_SYS386IGT ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  apic_id ; 
 int /*<<< orphan*/  assign_cpu_ids () ; 
 int boot_cpu_id ; 
 int* cpu_apic_ids ; 
 TYPE_1__* cpu_info ; 
 int /*<<< orphan*/  cpustop ; 
 int /*<<< orphan*/  cpususpend ; 
 int /*<<< orphan*/  invlcache ; 
 int /*<<< orphan*/  invlpg ; 
 int /*<<< orphan*/  invlrng ; 
 int /*<<< orphan*/  invltlb ; 
 int /*<<< orphan*/  ipi_intr_bitmap_handler ; 
 int /*<<< orphan*/  rendezvous ; 
 int /*<<< orphan*/  set_interrupt_apic_ids () ; 
 int /*<<< orphan*/  setidt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_all_aps () ; 
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
	setidt(IPI_INVLTLB, IDTVEC(invltlb),
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));
	setidt(IPI_INVLPG, IDTVEC(invlpg),
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));
	setidt(IPI_INVLRNG, IDTVEC(invlrng),
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));

	/* Install an inter-CPU IPI for cache invalidation. */
	setidt(IPI_INVLCACHE, IDTVEC(invlcache),
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));

	/* Install an inter-CPU IPI for all-CPU rendezvous */
	setidt(IPI_RENDEZVOUS, IDTVEC(rendezvous),
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));

	/* Install generic inter-CPU IPI handler */
	setidt(IPI_BITMAP_VECTOR, IDTVEC(ipi_intr_bitmap_handler),
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));

	/* Install an inter-CPU IPI for CPU stop/restart */
	setidt(IPI_STOP, IDTVEC(cpustop),
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));

	/* Install an inter-CPU IPI for CPU suspend/resume */
	setidt(IPI_SUSPEND, IDTVEC(cpususpend),
	       SDT_SYS386IGT, SEL_KPL, GSEL(GCODE_SEL, SEL_KPL));

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
	start_all_aps();

	set_interrupt_apic_ids();
}