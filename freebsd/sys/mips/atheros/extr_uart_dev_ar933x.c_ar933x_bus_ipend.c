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
typedef  int uint32_t ;
struct uart_bas {int dummy; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; scalar_t__ sc_txbusy; struct uart_bas sc_bas; } ;
struct ar933x_softc {int u_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_INT_EN_REG ; 
 int /*<<< orphan*/  AR933X_UART_INT_REG ; 
 int AR933X_UART_INT_RX_VALID ; 
 int AR933X_UART_INT_TX_EMPTY ; 
 int SER_INT_RXREADY ; 
 int SER_INT_SIGCHG ; 
 int SER_INT_TXIDLE ; 
 int ar933x_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar933x_bus_ipend(struct uart_softc *sc)
{
	struct ar933x_softc *u = (struct ar933x_softc *)sc;
	struct uart_bas *bas = &sc->sc_bas;
	int ipend = 0;
	uint32_t isr;

	uart_lock(sc->sc_hwmtx);

	/*
	 * Fetch/ACK the ISR status.
	 */
	isr = ar933x_getreg(bas, AR933X_UART_INT_REG);
	ar933x_setreg(bas, AR933X_UART_INT_REG, isr);
	uart_barrier(bas);

	/*
	 * RX ready - notify upper layer.
	 */
	if (isr & AR933X_UART_INT_RX_VALID) {
		ipend |= SER_INT_RXREADY;
	}

	/*
	 * If we get this interrupt, we should disable
	 * it from the interrupt mask and inform the uart
	 * driver appropriately.
	 *
	 * We can't keep setting SER_INT_TXIDLE or SER_INT_SIGCHG
	 * all the time or IO stops working.  So we will always
	 * clear this interrupt if we get it, then we only signal
	 * the upper layer if we were doing active TX in the
	 * first place.
	 *
	 * Also, the name is misleading.  This actually means
	 * "the FIFO is almost empty."  So if we just write some
	 * more data to the FIFO without checking whether it can
	 * take said data, we'll overflow the thing.
	 *
	 * Unfortunately the FreeBSD uart device has no concept of
	 * partial UART writes - it expects that the whole buffer
	 * is written to the hardware.  Thus for now, ar933x_bus_transmit()
	 * will wait for the FIFO to finish draining before it pushes
	 * more frames into it.
	 */
	if (isr & AR933X_UART_INT_TX_EMPTY) {
		/*
		 * Update u_ier to disable TX notifications; update hardware
		 */
		u->u_ier &= ~AR933X_UART_INT_TX_EMPTY;
		ar933x_setreg(bas, AR933X_UART_INT_EN_REG, u->u_ier);
		uart_barrier(bas);
	}

	/*
	 * Only signal TX idle if we're not busy transmitting.
	 *
	 * XXX I never get _out_ of txbusy? Debug that!
	 */
	if (sc->sc_txbusy) {
		if (isr & AR933X_UART_INT_TX_EMPTY) {
			ipend |= SER_INT_TXIDLE;
		} else {
			ipend |= SER_INT_SIGCHG;
		}
	}

	uart_unlock(sc->sc_hwmtx);
	return (ipend);
}