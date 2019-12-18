#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; } ;
struct TYPE_4__ {TYPE_1__ ppsparam; } ;
struct uart_softc {int sc_ttypend; scalar_t__ sc_opened; TYPE_2__ sc_pps; } ;

/* Variables and functions */
 int PPS_CAPTUREBOTH ; 
 int /*<<< orphan*/  SER_INT_SIGCHG ; 
 int SER_INT_SIGMASK ; 
 int SER_MASK_STATE ; 
 int UART_GETSIG (struct uart_softc*) ; 
 int /*<<< orphan*/  atomic_cmpset_32 (int*,int,int) ; 
 int /*<<< orphan*/  uart_pps_process (struct uart_softc*,int) ; 
 int /*<<< orphan*/  uart_sched_softih (struct uart_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
uart_intr_sigchg(void *arg)
{
	struct uart_softc *sc = arg;
	int new, old, sig;

	sig = UART_GETSIG(sc);

	/*
	 * Time pulse counting support, invoked whenever the PPS parameters are
	 * currently set to capture either edge of the signal.
	 */
	if (sc->sc_pps.ppsparam.mode & PPS_CAPTUREBOTH) {
		uart_pps_process(sc, sig);
	}

	/*
	 * Keep track of signal changes, even when the device is not
	 * opened. This allows us to inform upper layers about a
	 * possible loss of DCD and thus the existence of a (possibly)
	 * different connection when we have DCD back, during the time
	 * that the device was closed.
	 */
	do {
		old = sc->sc_ttypend;
		new = old & ~SER_MASK_STATE;
		new |= sig & SER_INT_SIGMASK;
	} while (!atomic_cmpset_32(&sc->sc_ttypend, old, new));

	if (sc->sc_opened)
		uart_sched_softih(sc, SER_INT_SIGCHG);
	return (1);
}