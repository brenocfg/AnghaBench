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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;
struct uart_mu_softc {int aux_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_IER_REG ; 
 int IER_MASK_ALL ; 
 int /*<<< orphan*/  __uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uart_mu_bus_grab(struct uart_softc *sc)
{
	struct uart_mu_softc *psc;
	struct uart_bas *bas;

	psc = (struct uart_mu_softc *)sc;
	bas = &sc->sc_bas;

	/* Disable interrupts on switch to polling */
	uart_lock(sc->sc_hwmtx);
	__uart_setreg(bas, AUX_MU_IER_REG, psc->aux_ier &~IER_MASK_ALL);
	uart_unlock(sc->sc_hwmtx);
}