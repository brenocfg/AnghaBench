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
 int /*<<< orphan*/  SAB_CMDR ; 
 int /*<<< orphan*/  SAB_CMDR_RFRD ; 
 int /*<<< orphan*/  SAB_ISR0 ; 
 int SAB_ISR0_CDSC ; 
 int SAB_ISR0_RFO ; 
 int SAB_ISR0_RPF ; 
 int SAB_ISR0_TCD ; 
 int SAB_ISR0_TIME ; 
 int /*<<< orphan*/  SAB_ISR1 ; 
 int SAB_ISR1_ALLS ; 
 int SAB_ISR1_BRKT ; 
 int SAB_ISR1_CSC ; 
 int /*<<< orphan*/  SAB_STAR ; 
 int SAB_STAR_CEC ; 
 int SER_INT_BREAK ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_SIGCHG ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sab82532_bus_ipend(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int ipend;
	uint8_t isr0, isr1;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	isr0 = uart_getreg(bas, SAB_ISR0);
	isr1 = uart_getreg(bas, SAB_ISR1);
	uart_barrier(bas);
	if (isr0 & SAB_ISR0_TIME) {
		while (uart_getreg(bas, SAB_STAR) & SAB_STAR_CEC)
			;
		uart_setreg(bas, SAB_CMDR, SAB_CMDR_RFRD);
		uart_barrier(bas);
	}
	uart_unlock(sc->sc_hwmtx);

	ipend = 0;
	if (isr1 & SAB_ISR1_BRKT)
		ipend |= SER_INT_BREAK;
	if (isr0 & SAB_ISR0_RFO)
		ipend |= SER_INT_OVERRUN;
	if (isr0 & (SAB_ISR0_TCD|SAB_ISR0_RPF))
		ipend |= SER_INT_RXREADY;
	if ((isr0 & SAB_ISR0_CDSC) || (isr1 & SAB_ISR1_CSC))
		ipend |= SER_INT_SIGCHG;
	if (isr1 & SAB_ISR1_ALLS)
		ipend |= SER_INT_TXIDLE;

	return (ipend);
}