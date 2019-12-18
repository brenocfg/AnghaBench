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
typedef  int uint8_t ;
struct cbb_softc {int /*<<< orphan*/ * exca; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXCA_INTR ; 
 int exca_getb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_putb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
cbb_o2micro_power_hack(struct cbb_softc *sc)
{
	uint8_t reg;

	/*
	 * Issue #2: INT# not qualified with IRQ Routing Bit.  An
	 * unexpected PCI INT# may be generated during PC Card
	 * initialization even with the IRQ Routing Bit Set with some
	 * PC Cards.
	 *
	 * This is a two part issue.  The first part is that some of
	 * our older controllers have an issue in which the slot's PCI
	 * INT# is NOT qualified by the IRQ routing bit (PCI reg. 3Eh
	 * bit 7).  Regardless of the IRQ routing bit, if NO ISA IRQ
	 * is selected (ExCA register 03h bits 3:0, of the slot, are
	 * cleared) we will generate INT# if IREQ# is asserted.  The
	 * second part is because some PC Cards prematurally assert
	 * IREQ# before the ExCA registers are fully programmed.  This
	 * in turn asserts INT# because ExCA register 03h bits 3:0
	 * (ISA IRQ Select) are not yet programmed.
	 *
	 * The fix for this issue, which will work for any controller
	 * (old or new), is to set ExCA register 03h bits 3:0 = 0001b
	 * (select IRQ1), of the slot, before turning on slot power.
	 * Selecting IRQ1 will result in INT# NOT being asserted
	 * (because IRQ1 is selected), and IRQ1 won't be asserted
	 * because our controllers don't generate IRQ1.
	 *
	 * Other, non O2Micro controllers will generate irq 1 in some
	 * situations, so we can't do this hack for everybody.  Reports of
	 * keyboard controller's interrupts being suppressed occurred when
	 * we did this.
	 */
	reg = exca_getb(&sc->exca[0], EXCA_INTR);
	exca_putb(&sc->exca[0], EXCA_INTR, (reg & 0xf0) | 1);
	return (reg);
}