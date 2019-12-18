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
typedef  int u_char ;
struct uart_bas {int dummy; } ;
struct uart_softc {struct uart_bas sc_bas; } ;
struct ns8250_softc {int ier_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  ns8250_clrint (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

int
ns8250_bus_detach(struct uart_softc *sc)
{
	struct ns8250_softc *ns8250;
	struct uart_bas *bas;
	u_char ier;

	ns8250 = (struct ns8250_softc *)sc;
	bas = &sc->sc_bas;
	ier = uart_getreg(bas, REG_IER) & ns8250->ier_mask;
	uart_setreg(bas, REG_IER, ier);
	uart_barrier(bas);
	ns8250_clrint(bas);
	return (0);
}