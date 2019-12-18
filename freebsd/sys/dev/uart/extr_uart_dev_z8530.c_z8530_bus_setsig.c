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
struct z8530_softc {int /*<<< orphan*/  tpc; } ;
struct uart_bas {int dummy; } ;
struct uart_softc {int sc_hwsig; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int SER_DDTR ; 
 int SER_DRTS ; 
 int SER_DTR ; 
 int SER_RTS ; 
 int /*<<< orphan*/  SIGCHG (int,int,int,int) ; 
 int /*<<< orphan*/  TPC_DTR ; 
 int /*<<< orphan*/  TPC_RTS ; 
 int /*<<< orphan*/  WR_TPC ; 
 int /*<<< orphan*/  atomic_cmpset_32 (int*,int,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setmreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
z8530_bus_setsig(struct uart_softc *sc, int sig)
{
	struct z8530_softc *z8530 = (struct z8530_softc*)sc;
	struct uart_bas *bas;
	uint32_t new, old;

	bas = &sc->sc_bas;
	do {
		old = sc->sc_hwsig;
		new = old;
		if (sig & SER_DDTR) {
			SIGCHG(sig & SER_DTR, new, SER_DTR,
			    SER_DDTR);
		}
		if (sig & SER_DRTS) {
			SIGCHG(sig & SER_RTS, new, SER_RTS,
			    SER_DRTS);
		}
	} while (!atomic_cmpset_32(&sc->sc_hwsig, old, new));

	uart_lock(sc->sc_hwmtx);
	if (new & SER_DTR)
		z8530->tpc |= TPC_DTR;
	else
		z8530->tpc &= ~TPC_DTR;
	if (new & SER_RTS)
		z8530->tpc |= TPC_RTS;
	else
		z8530->tpc &= ~TPC_RTS;
	uart_setmreg(bas, WR_TPC, z8530->tpc);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
	return (0);
}