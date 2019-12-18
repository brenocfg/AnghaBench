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
typedef  int uint8_t ;
struct uart_bas {int dummy; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB_IMR0 ; 
 int SAB_IMR0_CDSC ; 
 int SAB_IMR0_RFO ; 
 int SAB_IMR0_TIME ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sab82532_bus_grab(struct uart_softc *sc)
{
	struct uart_bas *bas;
	uint8_t imr0;

	bas = &sc->sc_bas;
	imr0 = SAB_IMR0_TIME|SAB_IMR0_CDSC|SAB_IMR0_RFO; /* No TCD or RPF */
	uart_lock(sc->sc_hwmtx);
	uart_setreg(bas, SAB_IMR0, 0xff & ~imr0);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
}