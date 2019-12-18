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
struct uart_softc {int /*<<< orphan*/  sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNC_UART_IEN_REG ; 
 int CDNC_UART_INT_DMSI ; 
 int CDNC_UART_INT_RXOVR ; 
 int CDNC_UART_INT_TXOVR ; 
 int /*<<< orphan*/  WR4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cdnc_uart_bus_grab(struct uart_softc *sc)
{

	/* Enable interrupts. */
	WR4(&sc->sc_bas, CDNC_UART_IEN_REG,
	    CDNC_UART_INT_TXOVR | CDNC_UART_INT_RXOVR |
	    CDNC_UART_INT_DMSI);
}