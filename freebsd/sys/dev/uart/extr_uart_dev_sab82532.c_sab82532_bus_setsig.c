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
struct uart_bas {int chan; } ;
struct uart_softc {int sc_hwsig; int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB_MODE ; 
 int /*<<< orphan*/  SAB_MODE_FRTS ; 
 int /*<<< orphan*/  SAB_PVR ; 
 int /*<<< orphan*/  SAB_PVR_DTR_A ; 
 int /*<<< orphan*/  SAB_PVR_DTR_B ; 
 int SER_DDTR ; 
 int SER_DRTS ; 
 int SER_DTR ; 
 int SER_RTS ; 
 int /*<<< orphan*/  SIGCHG (int,int,int,int) ; 
 int /*<<< orphan*/  atomic_cmpset_32 (int*,int,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sab82532_bus_setsig(struct uart_softc *sc, int sig)
{
	struct uart_bas *bas;
	uint32_t new, old;
	uint8_t mode, pvr;

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
	/* Set DTR pin. */
	pvr = uart_getreg(bas, SAB_PVR);
	switch (bas->chan) {
	case 1:
		if (new & SER_DTR)
			pvr &= ~SAB_PVR_DTR_A;
		else
			pvr |= SAB_PVR_DTR_A;
		break;
	case 2:
		if (new & SER_DTR)
			pvr &= ~SAB_PVR_DTR_B;
		else
			pvr |= SAB_PVR_DTR_B;
		break;
	}
	uart_setreg(bas, SAB_PVR, pvr);

	/* Set RTS pin. */
	mode = uart_getreg(bas, SAB_MODE);
	if (new & SER_RTS)
		mode &= ~SAB_MODE_FRTS;
	else
		mode |= SAB_MODE_FRTS;
	uart_setreg(bas, SAB_MODE, mode);
	uart_barrier(bas);
	uart_unlock(sc->sc_hwmtx);
	return (0);
}