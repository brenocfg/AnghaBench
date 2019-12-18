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
struct uart_softc {int sc_hwsig; } ;

/* Variables and functions */
 int /*<<< orphan*/  SER_CTS ; 
 int /*<<< orphan*/  SER_DCD ; 
 int /*<<< orphan*/  SER_DCTS ; 
 int /*<<< orphan*/  SER_DDCD ; 
 int /*<<< orphan*/  SER_DDSR ; 
 int /*<<< orphan*/  SER_DSR ; 
 int SER_MASK_DELTA ; 
 int /*<<< orphan*/  SIGCHG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_cmpset_32 (int*,int,int) ; 

__attribute__((used)) static int
aml8726_uart_bus_getsig(struct uart_softc *sc)
{
	uint32_t new, old, sig;

	/*
	 * Treat DSR, DCD, and CTS as always on.
	 */

	do {
		old = sc->sc_hwsig;
		sig = old;
		SIGCHG(1, sig, SER_DSR, SER_DDSR);
		SIGCHG(1, sig, SER_DCD, SER_DDCD);
		SIGCHG(1, sig, SER_CTS, SER_DCTS);
		new = sig & ~SER_MASK_DELTA;
	} while (!atomic_cmpset_32(&sc->sc_hwsig, old, new));

	return (sig);
}