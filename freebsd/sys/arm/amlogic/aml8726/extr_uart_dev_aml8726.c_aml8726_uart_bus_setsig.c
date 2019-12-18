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
typedef  int /*<<< orphan*/  uint32_t ;
struct uart_softc {int /*<<< orphan*/  sc_hwsig; } ;

/* Variables and functions */
 int SER_DDTR ; 
 int SER_DRTS ; 
 int SER_DTR ; 
 int SER_RTS ; 
 int /*<<< orphan*/  SIGCHG (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  atomic_cmpset_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_uart_bus_setsig(struct uart_softc *sc, int sig)
{
	uint32_t new, old;

	do {
		old = sc->sc_hwsig;
		new = old;
		if (sig & SER_DDTR) {
			SIGCHG(sig & SER_DTR, new, SER_DTR, SER_DDTR);
		}
		if (sig & SER_DRTS) {
			SIGCHG(sig & SER_RTS, new, SER_RTS, SER_DRTS);
		}
	 } while (!atomic_cmpset_32(&sc->sc_hwsig, old, new));

	return (0);
}