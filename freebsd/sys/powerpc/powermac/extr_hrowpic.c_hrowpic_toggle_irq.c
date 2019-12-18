#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u_int ;
struct hrowpic_softc {int* sc_softreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPIC_ENABLE ; 
 size_t HPIC_INT_TO_BANK (int) ; 
 size_t HPIC_INT_TO_REGBIT (int) ; 
 int HROWPIC_IRQMAX ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  hrowpic_write_reg (struct hrowpic_softc*,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void
hrowpic_toggle_irq(struct hrowpic_softc *sc, int irq, int enable)
{
	u_int roffset;
	u_int rbit;

	KASSERT((irq > 0) && (irq <= HROWPIC_IRQMAX), ("en irq out of range"));

	/*
	 * Humor the SMP layer if it wants to set up an IPI handler.
	 */
	if (irq == HROWPIC_IRQMAX)
		return;

	/*
	 * Calculate prim/sec register bank for the IRQ, update soft copy,
	 * and enable the IRQ as an interrupt source
	 */
	roffset = HPIC_INT_TO_BANK(irq);
	rbit = HPIC_INT_TO_REGBIT(irq);

	if (enable)
		sc->sc_softreg[roffset] |= (1 << rbit);
	else
		sc->sc_softreg[roffset] &= ~(1 << rbit);
		
	hrowpic_write_reg(sc, HPIC_ENABLE, roffset, sc->sc_softreg[roffset]);
}