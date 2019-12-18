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
struct vtbe_softc {int opened; int /*<<< orphan*/  pio_recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIO_SETUP_IRQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vtbe_softc*) ; 
 int /*<<< orphan*/  PIO_TEARDOWN_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtbe_intr ; 

__attribute__((used)) static int
pio_enable_irq(struct vtbe_softc *sc, int enable)
{

	/*
	 * IRQ lines should be disabled while reprogram FPGA core.
	 */

	if (enable) {
		if (sc->opened == 0) {
			sc->opened = 1;
			PIO_SETUP_IRQ(sc->pio_recv, vtbe_intr, sc);
		}
	} else {
		if (sc->opened == 1) {
			PIO_TEARDOWN_IRQ(sc->pio_recv);
			sc->opened = 0;
		}
	}

	return (0);
}