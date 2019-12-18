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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_CS_HOST_INT_EN ; 
 int /*<<< orphan*/  AR933X_UART_CS_REG ; 
 int /*<<< orphan*/  ar933x_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar933x_bus_ungrab(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	uint32_t reg;

	/* Enable the host interrupt now */
	uart_lock(sc->sc_hwmtx);
	reg = ar933x_getreg(bas, AR933X_UART_CS_REG);
	reg |= AR933X_UART_CS_HOST_INT_EN;
	ar933x_setreg(bas, AR933X_UART_CS_REG, reg);
	uart_unlock(sc->sc_hwmtx);
}