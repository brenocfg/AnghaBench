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
struct uart_softc {int sc_pps_mode; scalar_t__ sc_pps_captime; int /*<<< orphan*/  sc_pps; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  PPS_CAPTUREASSERT ; 
 int /*<<< orphan*/  PPS_CAPTURECLEAR ; 
 int SBT_1MS ; 
 int SER_CTS ; 
 int SER_DCD ; 
 int SER_DELTA (int) ; 
#define  UART_PPS_CTS 129 
#define  UART_PPS_DCD 128 
 int UART_PPS_INVERT_PULSE ; 
 int UART_PPS_NARROW_PULSE ; 
 int UART_PPS_SIGNAL_MASK ; 
 scalar_t__ getsbinuptime () ; 
 int /*<<< orphan*/  pps_capture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pps_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uart_pps_process(struct uart_softc *sc, int ser_sig)
{
	sbintime_t now;
	int is_assert, pps_sig;

	/* Which signal is configured as PPS?  Early out if none. */
	switch(sc->sc_pps_mode & UART_PPS_SIGNAL_MASK) {
	case UART_PPS_CTS:
		pps_sig = SER_CTS;
		break;
	case UART_PPS_DCD:
		pps_sig = SER_DCD;
		break;
	default:
		return;
	}

	/* Early out if there is no change in the signal configured as PPS. */
	if ((ser_sig & SER_DELTA(pps_sig)) == 0)
		return;

	/*
	 * In narrow-pulse mode we need to synthesize both capture and clear
	 * events from a single "delta occurred" indication from the uart
	 * hardware because the pulse width is too narrow to reliably detect
	 * both edges.  However, when the pulse width is close to our interrupt
	 * processing latency we might intermittantly catch both edges.  To
	 * guard against generating spurious events when that happens, we use a
	 * separate timer to ensure at least half a second elapses before we
	 * generate another event.
	 */
	pps_capture(&sc->sc_pps);
	if (sc->sc_pps_mode & UART_PPS_NARROW_PULSE) {
		now = getsbinuptime();
		if (now > sc->sc_pps_captime + 500 * SBT_1MS) {
			sc->sc_pps_captime = now;
			pps_event(&sc->sc_pps, PPS_CAPTUREASSERT);
			pps_event(&sc->sc_pps, PPS_CAPTURECLEAR);
		}
	} else  {
		is_assert = ser_sig & pps_sig;
		if (sc->sc_pps_mode & UART_PPS_INVERT_PULSE)
			is_assert = !is_assert;
		pps_event(&sc->sc_pps, is_assert ? PPS_CAPTUREASSERT :
		    PPS_CAPTURECLEAR);
	}
}