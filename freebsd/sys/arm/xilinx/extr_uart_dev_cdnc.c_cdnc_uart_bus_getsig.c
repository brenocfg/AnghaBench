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
struct uart_bas {int dummy; } ;
struct uart_softc {int sc_hwsig; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNC_UART_MODEM_STAT_REG ; 
 int CDNC_UART_MODEM_STAT_REG_CTS ; 
 int CDNC_UART_MODEM_STAT_REG_DCD ; 
 int CDNC_UART_MODEM_STAT_REG_DSR ; 
 int CDNC_UART_MODEM_STAT_REG_RI ; 
 int RD4 (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SER_CTS ; 
 int /*<<< orphan*/  SER_DCD ; 
 int /*<<< orphan*/  SER_DCTS ; 
 int /*<<< orphan*/  SER_DDCD ; 
 int /*<<< orphan*/  SER_DDSR ; 
 int /*<<< orphan*/  SER_DRI ; 
 int /*<<< orphan*/  SER_DSR ; 
 int SER_MASK_DELTA ; 
 int /*<<< orphan*/  SER_RI ; 
 int /*<<< orphan*/  SIGCHG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_cmpset_32 (int*,int,int) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdnc_uart_bus_getsig(struct uart_softc *sc)
{
	struct uart_bas *bas = &sc->sc_bas;
	uint32_t new, old, sig;
	uint8_t modem_status;

	do {
		old = sc->sc_hwsig;
		sig = old;
		uart_lock(sc->sc_hwmtx);
		modem_status = RD4(bas, CDNC_UART_MODEM_STAT_REG);
		uart_unlock(sc->sc_hwmtx);
		SIGCHG(modem_status & CDNC_UART_MODEM_STAT_REG_DSR,
		       sig, SER_DSR, SER_DDSR);
		SIGCHG(modem_status & CDNC_UART_MODEM_STAT_REG_CTS,
		       sig, SER_CTS, SER_DCTS);
		SIGCHG(modem_status & CDNC_UART_MODEM_STAT_REG_DCD,
		       sig, SER_DCD, SER_DDCD);
		SIGCHG(modem_status & CDNC_UART_MODEM_STAT_REG_RI,
		       sig, SER_RI,  SER_DRI);
		new = sig & ~SER_MASK_DELTA;
	} while (!atomic_cmpset_32(&sc->sc_hwsig, old, new));
	return (sig);
}