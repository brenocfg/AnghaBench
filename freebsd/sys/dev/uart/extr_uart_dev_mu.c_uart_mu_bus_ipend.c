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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; scalar_t__ sc_txbusy; struct uart_bas sc_bas; } ;
struct uart_mu_softc {int aux_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_IER_REG ; 
 int /*<<< orphan*/  AUX_MU_IIR_REG ; 
 int /*<<< orphan*/  AUX_MU_LSR_REG ; 
 int IER_TXENABLE ; 
 int IIR_RXREADY ; 
 int IIR_TXREADY ; 
 int LSR_TXIDLE ; 
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int __uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_mu_bus_ipend(struct uart_softc *sc)
{
	struct uart_mu_softc *psc;
	struct uart_bas *bas;
	uint32_t ints;
	int ipend;
	
	psc = (struct uart_mu_softc *)sc;
	bas = &sc->sc_bas;

	uart_lock(sc->sc_hwmtx);
	ints = __uart_getreg(bas, AUX_MU_IIR_REG);
	ipend = 0;

	/*
	 * According to docs only one of IIR_RXREADY
	 * or IIR_TXREADY are valid eg. Only one or the other.
	 */
	if (ints & IIR_RXREADY) {
		ipend |= SER_INT_RXREADY;
	} else if (ints & IIR_TXREADY) {
		if (__uart_getreg(bas, AUX_MU_LSR_REG) & LSR_TXIDLE) {
			if (sc->sc_txbusy)
				ipend |= SER_INT_TXIDLE;

			/* Disable TX interrupt */
			__uart_setreg(bas, AUX_MU_IER_REG,
				      psc->aux_ier & ~IER_TXENABLE);
		}
	}

	uart_unlock(sc->sc_hwmtx);

	return (ipend);
}