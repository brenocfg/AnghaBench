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
struct uart_softc {scalar_t__ sc_txbusy; struct uart_bas sc_bas; } ;
struct uart_mu_softc {int aux_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_IER_REG ; 
 int /*<<< orphan*/  AUX_MU_IIR_REG ; 
 int IER_REQUIRED ; 
 int IER_RXENABLE ; 
 int IER_TXENABLE ; 
 int IIR_CLEAR ; 
 int /*<<< orphan*/  __uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
uart_mu_bus_attach(struct uart_softc *sc)
{
	struct uart_mu_softc *psc;
	struct uart_bas *bas;

	psc = (struct uart_mu_softc *)sc;
	bas = &sc->sc_bas;
	/* Clear interrupts */
	__uart_setreg(bas, AUX_MU_IIR_REG, IIR_CLEAR);
	/* Enable interrupts */
	psc->aux_ier = (IER_RXENABLE|IER_TXENABLE|IER_REQUIRED);
	__uart_setreg(bas, AUX_MU_IER_REG, psc->aux_ier);
	sc->sc_txbusy = 0;
	
	return (0);
}