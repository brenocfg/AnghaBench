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
typedef  int uint32_t ;
typedef  int u_int ;
struct openpic_cpcht_softc {int /*<<< orphan*/  sc_ht_mtx; } ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ht_base; int edge; int ht_source; } ;

/* Variables and functions */
 int HTAPIC_MASK ; 
 int HTAPIC_REQUEST_EOI ; 
 int HTAPIC_TRIGGER_LEVEL ; 
 int INTR_TRIGGER_EDGE ; 
 scalar_t__ PCIR_HT_COMMAND ; 
 TYPE_1__* cpcht_irqmap ; 
 struct openpic_cpcht_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int in32rb (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out32rb (scalar_t__,int) ; 
 int /*<<< orphan*/  out8rb (scalar_t__,int) ; 

__attribute__((used)) static void
openpic_cpcht_config(device_t dev, u_int irq, enum intr_trigger trig,
    enum intr_polarity pol)
{
	struct openpic_cpcht_softc *sc;
	uint32_t ht_irq;

	/*
	 * The interrupt settings for the MPIC are completely determined
	 * by the internal wiring in the northbridge. Real changes to these
	 * settings need to be negotiated with the remote IO-APIC on the HT
	 * link.
	 */

	sc = device_get_softc(dev);

	if (cpcht_irqmap != NULL && irq < 128 &&
	    cpcht_irqmap[irq].ht_base > 0 && !cpcht_irqmap[irq].edge) {
		mtx_lock_spin(&sc->sc_ht_mtx);

		/* Program the data port */
		out8rb(cpcht_irqmap[irq].ht_base + PCIR_HT_COMMAND,
		    0x10 + (cpcht_irqmap[irq].ht_source << 1));

		/* Grab the IRQ config register */
		ht_irq = in32rb(cpcht_irqmap[irq].ht_base + 4);

		/* Mask the IRQ while we fiddle settings */
		out32rb(cpcht_irqmap[irq].ht_base + 4, ht_irq | HTAPIC_MASK);
		
		/* Program the interrupt sense */
		ht_irq &= ~(HTAPIC_TRIGGER_LEVEL | HTAPIC_REQUEST_EOI);
		if (trig == INTR_TRIGGER_EDGE) {
			cpcht_irqmap[irq].edge = 1;
		} else {
			cpcht_irqmap[irq].edge = 0;
			ht_irq |= HTAPIC_TRIGGER_LEVEL | HTAPIC_REQUEST_EOI;
		}
		out32rb(cpcht_irqmap[irq].ht_base + 4, ht_irq);

		mtx_unlock_spin(&sc->sc_ht_mtx);
	}
}