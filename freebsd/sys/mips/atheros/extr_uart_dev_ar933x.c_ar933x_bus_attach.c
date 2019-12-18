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
typedef  int /*<<< orphan*/  uint32_t ;
struct uart_bas {int dummy; } ;
struct uart_softc {struct uart_bas sc_bas; } ;
struct ar933x_softc {int /*<<< orphan*/  u_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_CS_HOST_INT_EN ; 
 int /*<<< orphan*/  AR933X_UART_CS_REG ; 
 int /*<<< orphan*/  AR933X_UART_INT_EN_REG ; 
 int /*<<< orphan*/  AR933X_UART_INT_RX_VALID ; 
 int /*<<< orphan*/  ar933x_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar933x_bus_attach(struct uart_softc *sc)
{
	struct ar933x_softc *u = (struct ar933x_softc *)sc;
	struct uart_bas *bas = &sc->sc_bas;
	uint32_t reg;

	/* XXX TODO: flush transmitter */

	/*
	 * Setup initial interrupt notifications.
	 *
	 * XXX for now, just RX FIFO valid.
	 * Later on (when they're handled), also handle
	 * RX errors/overflow.
	 */
	u->u_ier = AR933X_UART_INT_RX_VALID;

	/* Enable RX interrupts to kick-start things */
	ar933x_setreg(bas, AR933X_UART_INT_EN_REG, u->u_ier);

	/* Enable the host interrupt now */
	reg = ar933x_getreg(bas, AR933X_UART_CS_REG);
	reg |= AR933X_UART_CS_HOST_INT_EN;
	ar933x_setreg(bas, AR933X_UART_CS_REG, reg);

	return (0);
}