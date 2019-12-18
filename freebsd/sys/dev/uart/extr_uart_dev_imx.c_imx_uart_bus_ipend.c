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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGTIM ; 
 int /*<<< orphan*/  ATEN ; 
 int /*<<< orphan*/  BKEN ; 
 int /*<<< orphan*/  BRCD ; 
 int /*<<< orphan*/  DIS (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FLD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RRDY ; 
 int /*<<< orphan*/  RRDYEN ; 
 int SER_INT_BREAK ; 
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRDY ; 
 int /*<<< orphan*/  TRDYEN ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UCR2 ; 
 int /*<<< orphan*/  UCR4 ; 
 int /*<<< orphan*/  USR1 ; 
 int /*<<< orphan*/  USR2 ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_uart_bus_ipend(struct uart_softc *sc)
{
	struct uart_bas *bas;
	int ipend;
	uint32_t usr1, usr2;
	uint32_t ucr1, ucr2, ucr4;

	bas = &sc->sc_bas;
	ipend = 0;

	uart_lock(sc->sc_hwmtx);

	/* Read pending interrupts */
	usr1 = GETREG(bas, REG(USR1));
	usr2 = GETREG(bas, REG(USR2));
	/* ACK interrupts */
	SETREG(bas, REG(USR1), usr1);
	SETREG(bas, REG(USR2), usr2);

	ucr1 = GETREG(bas, REG(UCR1));
	ucr2 = GETREG(bas, REG(UCR2));
	ucr4 = GETREG(bas, REG(UCR4));

	/* If we have reached tx low-water, we can tx some more now. */
	if ((usr1 & FLD(USR1, TRDY)) && (ucr1 & FLD(UCR1, TRDYEN))) {
		DIS(bas, UCR1, TRDYEN);
		ipend |= SER_INT_TXIDLE;
	}

	/*
	 * If we have reached the rx high-water, or if there are bytes in the rx
	 * fifo and no new data has arrived for 8 character periods (aging
	 * timer), we have input data to process.
	 */
	if (((usr1 & FLD(USR1, RRDY)) && (ucr1 & FLD(UCR1, RRDYEN))) || 
	    ((usr1 & FLD(USR1, AGTIM)) && (ucr2 & FLD(UCR2, ATEN)))) {
		DIS(bas, UCR1, RRDYEN);
		DIS(bas, UCR2, ATEN);
		ipend |= SER_INT_RXREADY;
	}

	/* A break can come in at any time, it never gets disabled. */
	if ((usr2 & FLD(USR2, BRCD)) && (ucr4 & FLD(UCR4, BKEN)))
		ipend |= SER_INT_BREAK;

	uart_unlock(sc->sc_hwmtx);

	return (ipend);
}