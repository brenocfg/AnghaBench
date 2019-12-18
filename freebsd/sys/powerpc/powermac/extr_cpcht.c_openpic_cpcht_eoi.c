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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ht_base; scalar_t__ apple_eoi; int ht_source; int eoi_data; int /*<<< orphan*/  edge; } ;

/* Variables and functions */
 scalar_t__ PCIR_HT_COMMAND ; 
 TYPE_1__* cpcht_irqmap ; 
 struct openpic_cpcht_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openpic_eoi (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  out32rb (scalar_t__,int) ; 
 int /*<<< orphan*/  out8rb (scalar_t__,int) ; 

__attribute__((used)) static void
openpic_cpcht_eoi(device_t dev, u_int irq, void *priv)
{
	struct openpic_cpcht_softc *sc;
	uint32_t off, mask;

	if (irq == 255)
		return;

	sc = device_get_softc(dev);

	if (cpcht_irqmap != NULL && irq < 128 &&
	    cpcht_irqmap[irq].ht_base > 0 && !cpcht_irqmap[irq].edge) {
		/* If this is an HT IRQ, acknowledge it at the remote APIC */

		if (cpcht_irqmap[irq].apple_eoi) {
			off = (cpcht_irqmap[irq].ht_source >> 3) & ~3;
			mask = 1 << (cpcht_irqmap[irq].ht_source & 0x1f);
			out32rb(cpcht_irqmap[irq].apple_eoi + off, mask);
		} else {
			mtx_lock_spin(&sc->sc_ht_mtx);

			out8rb(cpcht_irqmap[irq].ht_base + PCIR_HT_COMMAND,
			    0x11 + (cpcht_irqmap[irq].ht_source << 1));
			out32rb(cpcht_irqmap[irq].ht_base + 4,
			    cpcht_irqmap[irq].eoi_data);

			mtx_unlock_spin(&sc->sc_ht_mtx);
		}
	}

	openpic_eoi(dev, irq, priv);
}