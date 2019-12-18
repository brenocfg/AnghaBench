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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct openpic_cpcht_softc {int /*<<< orphan*/  sc_ht_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ht_base; int ht_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTAPIC_MASK ; 
 scalar_t__ PCIR_HT_COMMAND ; 
 TYPE_1__* cpcht_irqmap ; 
 struct openpic_cpcht_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in32rb (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openpic_cpcht_eoi (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  openpic_enable (int /*<<< orphan*/ ,int,int,void**) ; 
 int /*<<< orphan*/  out32rb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out8rb (scalar_t__,int) ; 

__attribute__((used)) static void
openpic_cpcht_enable(device_t dev, u_int irq, u_int vec, void **priv)
{
	struct openpic_cpcht_softc *sc;
	uint32_t ht_irq;

	openpic_enable(dev, irq, vec, priv);

	sc = device_get_softc(dev);

	if (cpcht_irqmap != NULL && irq < 128 &&
	    cpcht_irqmap[irq].ht_base > 0) {
		mtx_lock_spin(&sc->sc_ht_mtx);

		/* Program the data port */
		out8rb(cpcht_irqmap[irq].ht_base + PCIR_HT_COMMAND,
		    0x10 + (cpcht_irqmap[irq].ht_source << 1));

		/* Unmask the interrupt */
		ht_irq = in32rb(cpcht_irqmap[irq].ht_base + 4);
		ht_irq &= ~HTAPIC_MASK;
		out32rb(cpcht_irqmap[irq].ht_base + 4, ht_irq);

		mtx_unlock_spin(&sc->sc_ht_mtx);
	}
		
	openpic_cpcht_eoi(dev, irq, *priv);
}