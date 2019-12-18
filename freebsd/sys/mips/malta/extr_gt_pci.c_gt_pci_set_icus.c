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
struct gt_pci_softc {int sc_imask; int sc_elcr; int /*<<< orphan*/  sc_ioh_elcr; int /*<<< orphan*/  sc_st; int /*<<< orphan*/  sc_ioh_icu2; int /*<<< orphan*/  sc_ioh_icu1; } ;

/* Variables and functions */
 int PIC_OCW1 ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
gt_pci_set_icus(struct gt_pci_softc *sc)
{
	/* Enable the cascade IRQ (2) if 8-15 is enabled. */
	if ((sc->sc_imask & 0xff00) != 0xff00)
		sc->sc_imask &= ~(1U << 2);
	else
		sc->sc_imask |= (1U << 2);

	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu1, PIC_OCW1,
	    sc->sc_imask & 0xff);
	bus_space_write_1(sc->sc_st, sc->sc_ioh_icu2, PIC_OCW1,
	    (sc->sc_imask >> 8) & 0xff);

	bus_space_write_1(sc->sc_st, sc->sc_ioh_elcr, 0,
	    sc->sc_elcr & 0xff);
	bus_space_write_1(sc->sc_st, sc->sc_ioh_elcr, 1,
	    (sc->sc_elcr >> 8) & 0xff);
}