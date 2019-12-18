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
typedef  int uint32_t ;
struct uart_bas {int dummy; } ;
struct uart_softc {size_t sc_rxput; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/ * sc_rxbuf; struct uart_bas sc_bas; } ;
struct uart_mu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_IO_REG ; 
 int /*<<< orphan*/  AUX_MU_LSR_REG ; 
 int LSR_RXREADY ; 
 int /*<<< orphan*/  UART_STAT_OVERRUN ; 
 int __uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ uart_rx_full (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_mu_bus_receive(struct uart_softc *sc)
{
	struct uart_mu_softc *psc;
	struct uart_bas *bas;
	uint32_t lsr, xc;
	int rx;
	
	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	psc = (struct uart_mu_softc *)sc;
	
	lsr = __uart_getreg(bas, AUX_MU_LSR_REG);
	while (lsr & LSR_RXREADY) {
		xc = __uart_getreg(bas, AUX_MU_IO_REG);
		rx = xc & 0xff;
		if (uart_rx_full(sc)) {
			sc->sc_rxbuf[sc->sc_rxput] = UART_STAT_OVERRUN;
			break;
		}
		uart_rx_put(sc, rx);
		lsr = __uart_getreg(bas, AUX_MU_LSR_REG);
	}
	uart_unlock(sc->sc_hwmtx);

	return (0);
}