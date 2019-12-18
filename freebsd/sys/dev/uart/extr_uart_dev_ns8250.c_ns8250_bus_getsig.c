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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct uart_softc {int sc_hwsig; int sc_pps_mode; int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/  sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTS ; 
 int /*<<< orphan*/  DCD ; 
 int /*<<< orphan*/  DSR ; 
 int /*<<< orphan*/  REG_MSR ; 
 int /*<<< orphan*/  RI ; 
 int SER_MASK_DELTA ; 
 int /*<<< orphan*/  SIGCHGHW (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGCHGSW (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UART_PPS_NARROW_PULSE ; 
 int /*<<< orphan*/  atomic_cmpset_32 (int*,int,int) ; 
 int /*<<< orphan*/  uart_getreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

int
ns8250_bus_getsig(struct uart_softc *sc)
{
	uint32_t old, sig;
	uint8_t msr;

	/*
	 * The delta bits are reputed to be broken on some hardware, so use
	 * software delta detection by default.  Use the hardware delta bits
	 * when capturing PPS pulses which are too narrow for software detection
	 * to see the edges.  Hardware delta for RI doesn't work like the
	 * others, so always use software for it.  Other threads may be changing
	 * other (non-MSR) bits in sc_hwsig, so loop until it can successfully
	 * update without other changes happening.  Note that the SIGCHGxx()
	 * macros carefully preserve the delta bits when we have to loop several
	 * times and a signal transitions between iterations.
	 */
	do {
		old = sc->sc_hwsig;
		sig = old;
		uart_lock(sc->sc_hwmtx);
		msr = uart_getreg(&sc->sc_bas, REG_MSR);
		uart_unlock(sc->sc_hwmtx);
		if (sc->sc_pps_mode & UART_PPS_NARROW_PULSE) {
			SIGCHGHW(sig, msr, DSR);
			SIGCHGHW(sig, msr, CTS);
			SIGCHGHW(sig, msr, DCD);
		} else {
			SIGCHGSW(sig, msr, DSR);
			SIGCHGSW(sig, msr, CTS);
			SIGCHGSW(sig, msr, DCD);
		}
		SIGCHGSW(sig, msr, RI);
	} while (!atomic_cmpset_32(&sc->sc_hwsig, old, sig & ~SER_MASK_DELTA));
	return (sig);
}