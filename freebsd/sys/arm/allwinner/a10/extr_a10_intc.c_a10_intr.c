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
typedef  int u_int ;
struct a10_aintc_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* isrcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_intr_frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  isrc; } ;

/* Variables and functions */
 int A10_INTR_MAX_NIRQS ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  a10_intr_eoi (struct a10_aintc_softc*,int) ; 
 int /*<<< orphan*/  a10_intr_mask (struct a10_aintc_softc*,int) ; 
 int a10_pending_irq (struct a10_aintc_softc*) ; 
 int /*<<< orphan*/  arm_irq_memory_barrier (int) ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10_intr(void *arg)
{
	struct a10_aintc_softc *sc = arg;
	u_int irq;

	irq = a10_pending_irq(sc);
	if (irq == -1 || irq > A10_INTR_MAX_NIRQS) {
		device_printf(sc->sc_dev, "Spurious interrupt %d\n", irq);
		return (FILTER_HANDLED);
	}

	while (irq != -1) {
		if (irq > A10_INTR_MAX_NIRQS) {
			device_printf(sc->sc_dev, "Spurious interrupt %d\n",
			    irq);
			return (FILTER_HANDLED);
		}
		if (intr_isrc_dispatch(&sc->isrcs[irq].isrc,
		    curthread->td_intr_frame) != 0) {
			a10_intr_mask(sc, irq);
			a10_intr_eoi(sc, irq);
			device_printf(sc->sc_dev,
			    "Stray interrupt %d disabled\n", irq);
		}

		arm_irq_memory_barrier(irq);
		irq = a10_pending_irq(sc);
	}

	return (FILTER_HANDLED);
}