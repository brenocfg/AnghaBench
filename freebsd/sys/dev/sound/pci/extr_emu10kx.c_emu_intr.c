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
struct emu_sc_info {int dbg_level; int /*<<< orphan*/  dev; scalar_t__ is_ca0102; scalar_t__ is_ca0108; TYPE_1__* ihandler; } ;
struct TYPE_2__ {int intr_mask; int (* irq_func ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_IPR ; 
 int /*<<< orphan*/  EMU_IPR2 ; 
 int /*<<< orphan*/  EMU_IPR3 ; 
 int EMU_MAX_IRQ_CONSUMERS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int emu_rd (struct emu_sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr (struct emu_sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
emu_intr(void *p)
{
	struct emu_sc_info *sc = (struct emu_sc_info *)p;
	uint32_t stat, ack;
	int i;

	for (;;) {
		stat = emu_rd(sc, EMU_IPR, 4);
		ack = 0;
		if (stat == 0)
			break;
		emu_wr(sc, EMU_IPR, stat, 4);
		for (i = 0; i < EMU_MAX_IRQ_CONSUMERS; i++) {
			if ((((sc->ihandler[i].intr_mask) & stat) != 0) &&
			    (((void *)sc->ihandler[i].irq_func) != NULL)) {
				ack |= sc->ihandler[i].irq_func(sc->ihandler[i].softc,
				    (sc->ihandler[i].intr_mask) & stat);
			}
		}
	if (sc->dbg_level > 1)
		if (stat & (~ack))
			device_printf(sc->dev, "Unhandled interrupt: %08x\n", stat & (~ack));

	}

	if ((sc->is_ca0102) || (sc->is_ca0108))
		for (;;) {
			stat = emu_rd(sc, EMU_IPR2, 4);
			ack = 0;
			if (stat == 0)
				break;
			emu_wr(sc, EMU_IPR2, stat, 4);
			if (sc->dbg_level > 1)
				device_printf(sc->dev, "EMU_IPR2: %08x\n", stat);

			break;	/* to avoid infinite loop. should be removed
				 * after completion of P16V interface. */
		}

	if (sc->is_ca0102)
		for (;;) {
			stat = emu_rd(sc, EMU_IPR3, 4);
			ack = 0;
			if (stat == 0)
				break;
			emu_wr(sc, EMU_IPR3, stat, 4);
			if (sc->dbg_level > 1)
				device_printf(sc->dev, "EMU_IPR3: %08x\n", stat);

			break;	/* to avoid infinite loop. should be removed
				 * after completion of S/PDIF interface */
		}
}