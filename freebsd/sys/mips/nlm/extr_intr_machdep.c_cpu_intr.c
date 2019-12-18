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
typedef  int uint64_t ;
struct trapframe {int dummy; } ;
struct intr_event {int dummy; } ;
typedef  int /*<<< orphan*/  eirr ;
struct TYPE_2__ {struct intr_event* ie; } ;

/* Variables and functions */
#define  IRQ_IPI 129 
#define  IRQ_MSGRING 128 
 int IRQ_TIMER ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 scalar_t__ intr_event_handle (struct intr_event*,struct trapframe*) ; 
 int /*<<< orphan*/ * mips_intr_counters ; 
 int /*<<< orphan*/  mips_intrcnt_inc (int /*<<< orphan*/ ) ; 
 int nlm_read_c0_eimr () ; 
 int nlm_read_c0_eirr () ; 
 int /*<<< orphan*/  nlm_write_c0_eirr (unsigned long long) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_1__* xlp_interrupts ; 

void
cpu_intr(struct trapframe *tf)
{
	struct intr_event *ie;
	uint64_t eirr, eimr;
	int i;

	critical_enter();

	/* find a list of enabled interrupts */
	eirr = nlm_read_c0_eirr();
	eimr = nlm_read_c0_eimr();
	eirr &= eimr;

	if (eirr == 0) {
		critical_exit();
		return;
	}
	/*
	 * No need to clear the EIRR here as the handler writes to
	 * compare which ACKs the interrupt.
	 */
	if (eirr & (1 << IRQ_TIMER)) {
		intr_event_handle(xlp_interrupts[IRQ_TIMER].ie, tf);
		critical_exit();
		return;
	}

	/* FIXME sched pin >? LOCK>? */
	for (i = sizeof(eirr) * 8 - 1; i >= 0; i--) {
		if ((eirr & (1ULL << i)) == 0)
			continue;

		ie = xlp_interrupts[i].ie;
		/* Don't account special IRQs */
		switch (i) {
		case IRQ_IPI:
		case IRQ_MSGRING:
			break;
		default:
			mips_intrcnt_inc(mips_intr_counters[i]);
		}

		/* Ack the IRQ on the CPU */
		nlm_write_c0_eirr(1ULL << i);
		if (intr_event_handle(ie, tf) != 0) {
			printf("stray interrupt %d\n", i);
		}
	}
	critical_exit();
}