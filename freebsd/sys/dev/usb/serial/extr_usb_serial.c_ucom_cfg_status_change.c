#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usb_proc_msg {int dummy; } ;
struct TYPE_6__ {int mode; } ;
struct TYPE_7__ {TYPE_2__ ppsparam; } ;
struct ucom_softc {int sc_flag; int sc_msr; int sc_lsr; TYPE_3__ sc_pps; TYPE_1__* sc_callback; struct tty* sc_tty; } ;
struct ucom_cfg_task {struct ucom_softc* sc; } ;
struct tty {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ucom_cfg_get_status ) (struct ucom_softc*,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PPS_CAPTUREASSERT ; 
 int PPS_CAPTUREBOTH ; 
 int /*<<< orphan*/  PPS_CAPTURECLEAR ; 
 int SER_CTS ; 
 int SER_DCD ; 
 int /*<<< orphan*/  TRE_BREAK ; 
 int /*<<< orphan*/  TRE_FRAMING ; 
 int /*<<< orphan*/  TRE_PARITY ; 
#define  UART_PPS_CTS 129 
#define  UART_PPS_DCD 128 
 int UART_PPS_INVERT_PULSE ; 
 int UART_PPS_SIGNAL_MASK ; 
 int UCOM_FLAG_HL_READY ; 
 int UCOM_FLAG_LL_READY ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 int ULSR_BI ; 
 int ULSR_FE ; 
 int ULSR_PE ; 
 int /*<<< orphan*/  pps_capture (TYPE_3__*) ; 
 int /*<<< orphan*/  pps_event (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ucom_softc*,int*,int*) ; 
 int /*<<< orphan*/  ttydisc_modem (struct tty*,int) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int ucom_pps_mode ; 

__attribute__((used)) static void
ucom_cfg_status_change(struct usb_proc_msg *_task)
{
	struct ucom_cfg_task *task = 
	    (struct ucom_cfg_task *)_task;
	struct ucom_softc *sc = task->sc;
	struct tty *tp;
	int onoff;
	uint8_t new_msr;
	uint8_t new_lsr;
	uint8_t msr_delta;
	uint8_t lsr_delta;
	uint8_t pps_signal;

	tp = sc->sc_tty;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	if (!(sc->sc_flag & UCOM_FLAG_LL_READY)) {
		return;
	}
	if (sc->sc_callback->ucom_cfg_get_status == NULL) {
		return;
	}
	/* get status */

	new_msr = 0;
	new_lsr = 0;

	(sc->sc_callback->ucom_cfg_get_status) (sc, &new_lsr, &new_msr);

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		/* TTY device closed */
		return;
	}
	msr_delta = (sc->sc_msr ^ new_msr);
	lsr_delta = (sc->sc_lsr ^ new_lsr);

	sc->sc_msr = new_msr;
	sc->sc_lsr = new_lsr;

	/*
	 * Time pulse counting support.
	 */
	switch(ucom_pps_mode & UART_PPS_SIGNAL_MASK) {
	case UART_PPS_CTS:
		pps_signal = SER_CTS;
		break;
	case UART_PPS_DCD:
		pps_signal = SER_DCD;
		break;
	default:
		pps_signal = 0;
		break;
	}

	if ((sc->sc_pps.ppsparam.mode & PPS_CAPTUREBOTH) &&
	    (msr_delta & pps_signal)) {
		pps_capture(&sc->sc_pps);
		onoff = (sc->sc_msr & pps_signal) ? 1 : 0;
		if (ucom_pps_mode & UART_PPS_INVERT_PULSE)
			onoff = !onoff;
		pps_event(&sc->sc_pps, onoff ? PPS_CAPTUREASSERT :
		    PPS_CAPTURECLEAR);
	}

	if (msr_delta & SER_DCD) {

		onoff = (sc->sc_msr & SER_DCD) ? 1 : 0;

		DPRINTF("DCD changed to %d\n", onoff);

		ttydisc_modem(tp, onoff);
	}

	if ((lsr_delta & ULSR_BI) && (sc->sc_lsr & ULSR_BI)) {

		DPRINTF("BREAK detected\n");

		ttydisc_rint(tp, 0, TRE_BREAK);
		ttydisc_rint_done(tp);
	}

	if ((lsr_delta & ULSR_FE) && (sc->sc_lsr & ULSR_FE)) {

		DPRINTF("Frame error detected\n");

		ttydisc_rint(tp, 0, TRE_FRAMING);
		ttydisc_rint_done(tp);
	}

	if ((lsr_delta & ULSR_PE) && (sc->sc_lsr & ULSR_PE)) {

		DPRINTF("Parity error detected\n");

		ttydisc_rint(tp, 0, TRE_PARITY);
		ttydisc_rint_done(tp);
	}
}