#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct uart_softc {int sc_txdatasz; int sc_txbusy; TYPE_1__ sc_bas; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/ * sc_txbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCOM_UINTM ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exynos4210_putc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_barrier (TYPE_1__*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exynos4210_bus_transmit(struct uart_softc *sc)
{
	int i;
	int reg;

	uart_lock(sc->sc_hwmtx);

	for (i = 0; i < sc->sc_txdatasz; i++) {
		exynos4210_putc(&sc->sc_bas, sc->sc_txbuf[i]);
		uart_barrier(&sc->sc_bas);
	}

	sc->sc_txbusy = 1;

	uart_unlock(sc->sc_hwmtx);

	/* unmask TX interrupt */
	reg = bus_space_read_4(sc->sc_bas.bst, sc->sc_bas.bsh, SSCOM_UINTM);
	reg &= ~(1 << 2);
	bus_space_write_4(sc->sc_bas.bst, sc->sc_bas.bsh, SSCOM_UINTM, reg);

	return (0);
}