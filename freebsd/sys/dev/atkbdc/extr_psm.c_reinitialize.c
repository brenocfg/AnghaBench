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
struct psm_softc {int state; int /*<<< orphan*/  kbdc; int /*<<< orphan*/  unit; int /*<<< orphan*/  mode; int /*<<< orphan*/  lastinputerr; scalar_t__ pkterrors; scalar_t__ syncerrors; int /*<<< orphan*/  callout; int /*<<< orphan*/  watchdog; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int KBD_DISABLE_AUX_INT ; 
 int KBD_DISABLE_AUX_PORT ; 
 int KBD_DISABLE_KBD_INT ; 
 int KBD_DISABLE_KBD_PORT ; 
 int KBD_ENABLE_AUX_PORT ; 
 int KBD_KBD_CONTROL_BITS ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int PSM_EV_OPEN_A ; 
 int PSM_EV_OPEN_R ; 
 int PSM_OPEN ; 
 int PSM_VALID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_aux_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ doinitialize (struct psm_softc*,int /*<<< orphan*/ *) ; 
 int doopen (struct psm_softc*,int) ; 
 int /*<<< orphan*/  empty_aux_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flushpackets (struct psm_softc*) ; 
 int get_controller_command_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_get_device_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  restore_controller (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
reinitialize(struct psm_softc *sc, int doinit)
{
	int err;
	int c;
	int s;

	/* don't let anybody mess with the aux device */
	if (!kbdc_lock(sc->kbdc, TRUE))
		return (EIO);
	s = spltty();

	/* block our watchdog timer */
	sc->watchdog = FALSE;
	callout_stop(&sc->callout);

	/* save the current controller command byte */
	empty_both_buffers(sc->kbdc, 10);
	c = get_controller_command_byte(sc->kbdc);
	VLOG(2, (LOG_DEBUG,
	    "psm%d: current command byte: %04x (reinitialize).\n",
	    sc->unit, c));

	/* enable the aux port but disable the aux interrupt and the keyboard */
	if ((c == -1) || !set_controller_command_byte(sc->kbdc,
	    kbdc_get_device_mask(sc->kbdc),
	    KBD_DISABLE_KBD_PORT | KBD_DISABLE_KBD_INT |
	    KBD_ENABLE_AUX_PORT | KBD_DISABLE_AUX_INT)) {
		/* CONTROLLER ERROR */
		splx(s);
		kbdc_lock(sc->kbdc, FALSE);
		log(LOG_ERR,
		    "psm%d: unable to set the command byte (reinitialize).\n",
		    sc->unit);
		return (EIO);
	}

	/* flush any data */
	if (sc->state & PSM_VALID) {
		/* this may fail; but never mind... */
		disable_aux_dev(sc->kbdc);
		empty_aux_buffer(sc->kbdc, 10);
	}
	flushpackets(sc);
	sc->syncerrors = 0;
	sc->pkterrors = 0;
	memset(&sc->lastinputerr, 0, sizeof(sc->lastinputerr));

	/* try to detect the aux device; are you still there? */
	err = 0;
	if (doinit) {
		if (doinitialize(sc, &sc->mode)) {
			/* yes */
			sc->state |= PSM_VALID;
		} else {
			/* the device has gone! */
			restore_controller(sc->kbdc, c);
			sc->state &= ~PSM_VALID;
			log(LOG_ERR,
			    "psm%d: the aux device has gone! (reinitialize).\n",
			    sc->unit);
			err = ENXIO;
		}
	}
	splx(s);

	/* restore the driver state */
	if ((sc->state & (PSM_OPEN | PSM_EV_OPEN_R | PSM_EV_OPEN_A)) &&
	    (err == 0)) {
		/* enable the aux device and the port again */
		err = doopen(sc, c);
		if (err != 0)
			log(LOG_ERR, "psm%d: failed to enable the device "
			    "(reinitialize).\n", sc->unit);
	} else {
		/* restore the keyboard port and disable the aux port */
		if (!set_controller_command_byte(sc->kbdc,
		    kbdc_get_device_mask(sc->kbdc),
		    (c & KBD_KBD_CONTROL_BITS) |
		    KBD_DISABLE_AUX_PORT | KBD_DISABLE_AUX_INT)) {
			/* CONTROLLER ERROR */
			log(LOG_ERR, "psm%d: failed to disable the aux port "
			    "(reinitialize).\n", sc->unit);
			err = EIO;
		}
	}

	kbdc_lock(sc->kbdc, FALSE);
	return (err);
}