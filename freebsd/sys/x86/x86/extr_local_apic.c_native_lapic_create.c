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
typedef  int u_int ;
struct TYPE_6__ {scalar_t__ lvt_active; } ;
struct TYPE_5__ {int la_present; int la_id; int /*<<< orphan*/ * la_ioint_irqs; TYPE_3__* la_elvts; TYPE_1__* la_lvts; } ;
struct TYPE_4__ {scalar_t__ lvt_active; } ;

/* Variables and functions */
 int APIC_ELVT_MAX ; 
 size_t APIC_IO_INTS ; 
 int APIC_LVT_MAX ; 
 int APIC_NUM_IOINTS ; 
 size_t APIC_TIMER_INT ; 
 size_t IDT_DTRACE_RET ; 
 size_t IDT_EVTCHN ; 
 size_t IDT_SYSCALL ; 
 int /*<<< orphan*/  IRQ_DTRACE_RET ; 
 int /*<<< orphan*/  IRQ_EVTCHN ; 
 int /*<<< orphan*/  IRQ_FREE ; 
 int /*<<< orphan*/  IRQ_SYSCALL ; 
 int /*<<< orphan*/  IRQ_TIMER ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  cpu_add (int,int) ; 
 TYPE_3__* elvts ; 
 TYPE_2__* lapics ; 
 TYPE_1__* lvts ; 
 int max_apic_id ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
native_lapic_create(u_int apic_id, int boot_cpu)
{
	int i;

	if (apic_id > max_apic_id) {
		printf("APIC: Ignoring local APIC with ID %d\n", apic_id);
		if (boot_cpu)
			panic("Can't ignore BSP");
		return;
	}
	KASSERT(!lapics[apic_id].la_present, ("duplicate local APIC %u",
	    apic_id));

	/*
	 * Assume no local LVT overrides and a cluster of 0 and
	 * intra-cluster ID of 0.
	 */
	lapics[apic_id].la_present = 1;
	lapics[apic_id].la_id = apic_id;
	for (i = 0; i <= APIC_LVT_MAX; i++) {
		lapics[apic_id].la_lvts[i] = lvts[i];
		lapics[apic_id].la_lvts[i].lvt_active = 0;
	}
	for (i = 0; i <= APIC_ELVT_MAX; i++) {
		lapics[apic_id].la_elvts[i] = elvts[i];
		lapics[apic_id].la_elvts[i].lvt_active = 0;
	}
	for (i = 0; i <= APIC_NUM_IOINTS; i++)
	    lapics[apic_id].la_ioint_irqs[i] = IRQ_FREE;
	lapics[apic_id].la_ioint_irqs[IDT_SYSCALL - APIC_IO_INTS] = IRQ_SYSCALL;
	lapics[apic_id].la_ioint_irqs[APIC_TIMER_INT - APIC_IO_INTS] =
	    IRQ_TIMER;
#ifdef KDTRACE_HOOKS
	lapics[apic_id].la_ioint_irqs[IDT_DTRACE_RET - APIC_IO_INTS] =
	    IRQ_DTRACE_RET;
#endif
#ifdef XENHVM
	lapics[apic_id].la_ioint_irqs[IDT_EVTCHN - APIC_IO_INTS] = IRQ_EVTCHN;
#endif


#ifdef SMP
	cpu_add(apic_id, boot_cpu);
#endif
}