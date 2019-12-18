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
struct trapframe {int tf_scause; } ;
struct intr_irqsrc {int dummy; } ;
struct TYPE_2__ {struct intr_irqsrc isrc; } ;

/* Variables and functions */
 int EXCP_INTR ; 
 int EXCP_MASK ; 
#define  IRQ_EXTERNAL_SUPERVISOR 131 
#define  IRQ_SOFTWARE_SUPERVISOR 130 
#define  IRQ_SOFTWARE_USER 129 
#define  IRQ_TIMER_SUPERVISOR 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  intr_irq_handler (struct trapframe*) ; 
 int /*<<< orphan*/  intr_isrc_dispatch (struct intr_irqsrc*,struct trapframe*) ; 
 TYPE_1__* isrcs ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void
riscv_cpu_intr(struct trapframe *frame)
{
	struct intr_irqsrc *isrc;
	int active_irq;

	critical_enter();

	KASSERT(frame->tf_scause & EXCP_INTR,
		("riscv_cpu_intr: wrong frame passed"));

	active_irq = (frame->tf_scause & EXCP_MASK);

	switch (active_irq) {
	case IRQ_SOFTWARE_USER:
	case IRQ_SOFTWARE_SUPERVISOR:
	case IRQ_TIMER_SUPERVISOR:
		isrc = &isrcs[active_irq].isrc;
		if (intr_isrc_dispatch(isrc, frame) != 0)
			printf("stray interrupt %d\n", active_irq);
		break;
	case IRQ_EXTERNAL_SUPERVISOR:
		intr_irq_handler(frame);
		break;
	default:
		break;
	}

	critical_exit();
}