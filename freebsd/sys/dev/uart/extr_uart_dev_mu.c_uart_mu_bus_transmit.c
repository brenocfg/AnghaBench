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
struct uart_bas {int dummy; } ;
struct uart_softc {int sc_txdatasz; int* sc_txbuf; int sc_txbusy; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct uart_mu_softc {int aux_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_IER_REG ; 
 int /*<<< orphan*/  AUX_MU_IO_REG ; 
 int /*<<< orphan*/  __uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_mu_bus_transmit(struct uart_softc *sc)
{
	struct uart_mu_softc *psc;
	struct uart_bas *bas;
	int i;
	
	psc = (struct uart_mu_softc *)sc;
	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);

  	for (i = 0; i < sc->sc_txdatasz; i++) {
		__uart_setreg(bas, AUX_MU_IO_REG, sc->sc_txbuf[i] & 0xff);
		uart_barrier(bas);
	}

	/* Mark busy and enable TX interrupt */
	sc->sc_txbusy = 1;
	__uart_setreg(bas, AUX_MU_IER_REG, psc->aux_ier);
		
	uart_unlock(sc->sc_hwmtx);

	return (0);
}