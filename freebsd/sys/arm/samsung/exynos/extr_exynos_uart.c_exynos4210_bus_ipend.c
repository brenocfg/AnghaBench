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
struct TYPE_2__ {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct uart_softc {scalar_t__ sc_txbusy; int /*<<< orphan*/  sc_hwmtx; TYPE_1__ sc_bas; } ;

/* Variables and functions */
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  SSCOM_UINTM ; 
 int /*<<< orphan*/  SSCOM_UINTP ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exynos4210_bus_ipend(struct uart_softc *sc)
{
	uint32_t ints;
	uint32_t txempty, rxready;
	int reg;
	int ipend;

	uart_lock(sc->sc_hwmtx);
	ints = bus_space_read_4(sc->sc_bas.bst, sc->sc_bas.bsh, SSCOM_UINTP);
	bus_space_write_4(sc->sc_bas.bst, sc->sc_bas.bsh, SSCOM_UINTP, ints);

	txempty = (1 << 2);
	rxready = (1 << 0);

	ipend = 0;
	if ((ints & txempty) > 0) {
		if (sc->sc_txbusy != 0)
			ipend |= SER_INT_TXIDLE;

		/* mask TX interrupt */
		reg = bus_space_read_4(sc->sc_bas.bst, sc->sc_bas.bsh,
		    SSCOM_UINTM);
		reg |= (1 << 2);
		bus_space_write_4(sc->sc_bas.bst, sc->sc_bas.bsh,
		    SSCOM_UINTM, reg);
	}

	if ((ints & rxready) > 0) {
		ipend |= SER_INT_RXREADY;
	}

	uart_unlock(sc->sc_hwmtx);
	return (ipend);
}