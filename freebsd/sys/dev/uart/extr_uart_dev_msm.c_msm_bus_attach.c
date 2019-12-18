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
struct uart_softc {scalar_t__ sc_hwoflow; scalar_t__ sc_hwiflow; struct uart_bas sc_bas; } ;
struct msm_uart_softc {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_DM_IMR ; 
 int /*<<< orphan*/  UART_DM_IMR_ENABLED ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msm_bus_attach(struct uart_softc *sc)
{
	struct msm_uart_softc *u = (struct msm_uart_softc *)sc;
	struct uart_bas *bas = &sc->sc_bas;

	sc->sc_hwiflow = 0;
	sc->sc_hwoflow = 0;

	/* Set TX_READY, TXLEV, RXLEV, RXSTALE */
	u->ier = UART_DM_IMR_ENABLED;

	/* Configure Interrupt Mask register IMR */
	uart_setreg(bas, UART_DM_IMR, u->ier);

	return (0);
}