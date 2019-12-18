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

/* Variables and functions */
 int /*<<< orphan*/  SAB_CCR0 ; 
 int /*<<< orphan*/  SAB_IMR0 ; 
 int /*<<< orphan*/  SAB_IMR1 ; 
 int /*<<< orphan*/  SAB_ISR0 ; 
 int /*<<< orphan*/  SAB_ISR1 ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sab82532_bus_detach(struct uart_softc *sc)
{
	struct uart_bas *bas;

	bas = &sc->sc_bas;
	uart_setreg(bas, SAB_IMR0, 0xff);
	uart_setreg(bas, SAB_IMR1, 0xff);
	uart_barrier(bas);
	uart_getreg(bas, SAB_ISR0);
	uart_getreg(bas, SAB_ISR1);
	uart_barrier(bas);
	uart_setreg(bas, SAB_CCR0, 0);
	uart_barrier(bas);
	return (0);
}