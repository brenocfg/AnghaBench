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
typedef  int uint32_t ;
struct z8530_softc {scalar_t__ txidle; } ;
struct uart_bas {int chan; } ;
struct uart_softc {int sc_hwsig; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int BES_BRK ; 
 int BES_CTS ; 
 int BES_DCD ; 
 int BES_SYNC ; 
 int /*<<< orphan*/  CR_RSTERR ; 
 int /*<<< orphan*/  CR_RSTIUS ; 
 int /*<<< orphan*/  CR_RSTTXI ; 
 int /*<<< orphan*/  CR_RSTXSI ; 
 int IP_RIA ; 
 int IP_SIA ; 
 int IP_TIA ; 
#define  IV_RAB 130 
#define  IV_TEB 129 
#define  IV_XSB 128 
 int /*<<< orphan*/  REG_CTRL ; 
 int /*<<< orphan*/  RR_BES ; 
 int /*<<< orphan*/  RR_IP ; 
 int /*<<< orphan*/  RR_IV ; 
 int /*<<< orphan*/  RR_SRC ; 
 int /*<<< orphan*/  SER_CTS ; 
 int /*<<< orphan*/  SER_DCD ; 
 int /*<<< orphan*/  SER_DCTS ; 
 int /*<<< orphan*/  SER_DDCD ; 
 int /*<<< orphan*/  SER_DDSR ; 
 int /*<<< orphan*/  SER_DSR ; 
 int SER_INT_BREAK ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_SIGCHG ; 
 int SER_INT_TXIDLE ; 
 int SER_MASK_DELTA ; 
 int /*<<< orphan*/  SIGCHG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SRC_OVR ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getmreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
z8530_bus_ipend(struct uart_softc *sc)
{
	struct z8530_softc *z8530 = (struct z8530_softc*)sc;
	struct uart_bas *bas;
	int ipend;
	uint32_t sig;
	uint8_t bes, ip, iv, src;

	bas = &sc->sc_bas;
	ipend = 0;

	uart_lock(sc->sc_hwmtx);
	switch (bas->chan) {
	case 1:
		ip = uart_getmreg(bas, RR_IP);
		break;
	case 2:	/* XXX hack!!! */
		iv = uart_getmreg(bas, RR_IV) & 0x0E;
		switch (iv) {
		case IV_TEB:	ip = IP_TIA; break;
		case IV_XSB:	ip = IP_SIA; break;
		case IV_RAB:	ip = IP_RIA; break;
		default:	ip = 0; break;
		}
		break;
	default:
		ip = 0;
		break;
	}

	if (ip & IP_RIA)
		ipend |= SER_INT_RXREADY;

	if (ip & IP_TIA) {
		uart_setreg(bas, REG_CTRL, CR_RSTTXI);
		uart_barrier(bas);
		if (z8530->txidle) {
			ipend |= SER_INT_TXIDLE;
			z8530->txidle = 0;	/* Mask SER_INT_TXIDLE. */
		}
	}

	if (ip & IP_SIA) {
		uart_setreg(bas, REG_CTRL, CR_RSTXSI);
		uart_barrier(bas);
		bes = uart_getmreg(bas, RR_BES);
		if (bes & BES_BRK)
			ipend |= SER_INT_BREAK;
		sig = sc->sc_hwsig;
		SIGCHG(bes & BES_CTS, sig, SER_CTS, SER_DCTS);
		SIGCHG(bes & BES_DCD, sig, SER_DCD, SER_DDCD);
		SIGCHG(bes & BES_SYNC, sig, SER_DSR, SER_DDSR);
		if (sig & SER_MASK_DELTA)
			ipend |= SER_INT_SIGCHG;
		src = uart_getmreg(bas, RR_SRC);
		if (src & SRC_OVR) {
			uart_setreg(bas, REG_CTRL, CR_RSTERR);
			uart_barrier(bas);
			ipend |= SER_INT_OVERRUN;
		}
	}

	if (ipend) {
		uart_setreg(bas, REG_CTRL, CR_RSTIUS);
		uart_barrier(bas);
	}

	uart_unlock(sc->sc_hwmtx);

	return (ipend);
}