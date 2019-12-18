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
struct trapframe {int dummy; } ;
struct gicv3_its_softc {scalar_t__ sc_irq_base; struct gicv3_its_irqsrc* sc_irqs; } ;
struct gicv3_its_irqsrc {int /*<<< orphan*/  gi_isrc; } ;
struct TYPE_2__ {struct trapframe* td_intr_frame; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  intr_isrc_dispatch (int /*<<< orphan*/ *,struct trapframe*) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 

__attribute__((used)) static int
gicv3_its_intr(void *arg, uintptr_t irq)
{
	struct gicv3_its_softc *sc = arg;
	struct gicv3_its_irqsrc *girq;
	struct trapframe *tf;

	irq -= sc->sc_irq_base;
	girq = &sc->sc_irqs[irq];
	if (girq == NULL)
		panic("gicv3_its_intr: Invalid interrupt %ld",
		    irq + sc->sc_irq_base);

	tf = curthread->td_intr_frame;
	intr_isrc_dispatch(&girq->gi_isrc, tf);
	return (FILTER_HANDLED);
}