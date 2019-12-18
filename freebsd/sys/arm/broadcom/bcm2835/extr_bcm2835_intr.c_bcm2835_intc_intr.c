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
struct bcm_intc_softc {int /*<<< orphan*/  sc_dev; TYPE_2__* intc_isrcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  bii_isrc; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_intr_frame; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 
 int bcm2835_intc_active_intr (struct bcm_intc_softc*) ; 
 int /*<<< orphan*/  bcm_intc_isrc_mask (struct bcm_intc_softc*,TYPE_2__*) ; 
 scalar_t__ bootverbose ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm2835_intc_intr(void *arg)
{
	int irq, num;
	struct bcm_intc_softc *sc = arg;

	for (num = 0; ; num++) {
		irq = bcm2835_intc_active_intr(sc);
		if (irq == -1)
			break;
		if (intr_isrc_dispatch(&sc->intc_isrcs[irq].bii_isrc,
		    curthread->td_intr_frame) != 0) {
			bcm_intc_isrc_mask(sc, &sc->intc_isrcs[irq]);
			device_printf(sc->sc_dev, "Stray irq %u disabled\n",
			    irq);
		}
		arm_irq_memory_barrier(0); /* XXX */
	}
	if (num == 0 && bootverbose)
		device_printf(sc->sc_dev, "Spurious interrupt detected\n");

	return (FILTER_HANDLED);
}