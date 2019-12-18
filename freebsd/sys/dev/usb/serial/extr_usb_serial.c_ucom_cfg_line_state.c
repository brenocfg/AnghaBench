#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usb_proc_msg {int dummy; } ;
struct ucom_softc {int sc_flag; int sc_pls_set; int sc_pls_clr; int sc_pls_curr; TYPE_1__* sc_callback; } ;
struct ucom_cfg_task {struct ucom_softc* sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ucom_cfg_set_ring ) (struct ucom_softc*,int) ;int /*<<< orphan*/  (* ucom_cfg_set_break ) (struct ucom_softc*,int) ;int /*<<< orphan*/  (* ucom_cfg_set_rts ) (struct ucom_softc*,int) ;int /*<<< orphan*/  (* ucom_cfg_set_dtr ) (struct ucom_softc*,int) ;} ;

/* Variables and functions */
 int UCOM_FLAG_LL_READY ; 
 int UCOM_LS_BREAK ; 
 int UCOM_LS_DTR ; 
 int UCOM_LS_RING ; 
 int UCOM_LS_RTS ; 
 int /*<<< orphan*/  stub1 (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  stub2 (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  stub3 (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  stub4 (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  stub5 (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  stub6 (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  stub7 (struct ucom_softc*,int) ; 
 int /*<<< orphan*/  stub8 (struct ucom_softc*,int) ; 

__attribute__((used)) static void
ucom_cfg_line_state(struct usb_proc_msg *_task)
{
	struct ucom_cfg_task *task = 
	    (struct ucom_cfg_task *)_task;
	struct ucom_softc *sc = task->sc;
	uint8_t notch_bits;
	uint8_t any_bits;
	uint8_t prev_value;
	uint8_t last_value;
	uint8_t mask;

	if (!(sc->sc_flag & UCOM_FLAG_LL_READY)) {
		return;
	}

	mask = 0;
	/* compute callback mask */
	if (sc->sc_callback->ucom_cfg_set_dtr)
		mask |= UCOM_LS_DTR;
	if (sc->sc_callback->ucom_cfg_set_rts)
		mask |= UCOM_LS_RTS;
	if (sc->sc_callback->ucom_cfg_set_break)
		mask |= UCOM_LS_BREAK;
	if (sc->sc_callback->ucom_cfg_set_ring)
		mask |= UCOM_LS_RING;

	/* compute the bits we are to program */
	notch_bits = (sc->sc_pls_set & sc->sc_pls_clr) & mask;
	any_bits = (sc->sc_pls_set | sc->sc_pls_clr) & mask;
	prev_value = sc->sc_pls_curr ^ notch_bits;
	last_value = sc->sc_pls_curr;

	/* reset programmed line state */
	sc->sc_pls_curr = 0;
	sc->sc_pls_set = 0;
	sc->sc_pls_clr = 0;

	/* ensure that we don't lose any levels */
	if (notch_bits & UCOM_LS_DTR)
		sc->sc_callback->ucom_cfg_set_dtr(sc,
		    (prev_value & UCOM_LS_DTR) ? 1 : 0);
	if (notch_bits & UCOM_LS_RTS)
		sc->sc_callback->ucom_cfg_set_rts(sc,
		    (prev_value & UCOM_LS_RTS) ? 1 : 0);
	if (notch_bits & UCOM_LS_BREAK)
		sc->sc_callback->ucom_cfg_set_break(sc,
		    (prev_value & UCOM_LS_BREAK) ? 1 : 0);
	if (notch_bits & UCOM_LS_RING)
		sc->sc_callback->ucom_cfg_set_ring(sc,
		    (prev_value & UCOM_LS_RING) ? 1 : 0);

	/* set last value */
	if (any_bits & UCOM_LS_DTR)
		sc->sc_callback->ucom_cfg_set_dtr(sc,
		    (last_value & UCOM_LS_DTR) ? 1 : 0);
	if (any_bits & UCOM_LS_RTS)
		sc->sc_callback->ucom_cfg_set_rts(sc,
		    (last_value & UCOM_LS_RTS) ? 1 : 0);
	if (any_bits & UCOM_LS_BREAK)
		sc->sc_callback->ucom_cfg_set_break(sc,
		    (last_value & UCOM_LS_BREAK) ? 1 : 0);
	if (any_bits & UCOM_LS_RING)
		sc->sc_callback->ucom_cfg_set_ring(sc,
		    (last_value & UCOM_LS_RING) ? 1 : 0);
}