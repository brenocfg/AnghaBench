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
struct uart_softc {struct uart_bas sc_bas; } ;
struct uart_pl011_softc {int imsc; } ;

/* Variables and functions */
 int IMSC_MASK_ALL ; 
 int RIS_RTIM ; 
 int /*<<< orphan*/  UART_ICR ; 
 int /*<<< orphan*/  UART_IMSC ; 
 int UART_RXREADY ; 
 int UART_TXEMPTY ; 
 int /*<<< orphan*/  __uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
uart_pl011_bus_attach(struct uart_softc *sc)
{
	struct uart_pl011_softc *psc;
	struct uart_bas *bas;

	psc = (struct uart_pl011_softc *)sc;
	bas = &sc->sc_bas;

	/* Enable interrupts */
	psc->imsc = (UART_RXREADY | RIS_RTIM | UART_TXEMPTY);
	__uart_setreg(bas, UART_IMSC, psc->imsc);

	/* Clear interrupts */
	__uart_setreg(bas, UART_ICR, IMSC_MASK_ALL);

	return (0);
}