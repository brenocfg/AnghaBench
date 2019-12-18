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
struct uart_softc {int sc_hwsig; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/  sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCDIN ; 
 int FLD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GETREG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SER_DCD ; 
 int /*<<< orphan*/  SER_DDCD ; 
 int SER_MASK_DELTA ; 
 int /*<<< orphan*/  SIGCHG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USR2 ; 
 int /*<<< orphan*/  atomic_cmpset_32 (int*,int,int) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_uart_bus_getsig(struct uart_softc *sc)
{
	uint32_t new, old, sig;
	uint8_t bes;

	do {
		old = sc->sc_hwsig;
		sig = old;
		uart_lock(sc->sc_hwmtx);
		bes = GETREG(&sc->sc_bas, REG(USR2));
		uart_unlock(sc->sc_hwmtx);
		/* XXX: chip can show delta */
		SIGCHG(bes & FLD(USR2, DCDIN), sig, SER_DCD, SER_DDCD);
		new = sig & ~SER_MASK_DELTA;
	} while (!atomic_cmpset_32(&sc->sc_hwsig, old, new));

	return (sig);
}