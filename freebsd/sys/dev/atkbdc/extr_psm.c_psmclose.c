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
struct psm_softc {int state; int /*<<< orphan*/  kbdc; int /*<<< orphan*/  unit; int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FALSE ; 
 int KBD_DISABLE_AUX_INT ; 
 int KBD_DISABLE_AUX_PORT ; 
 int KBD_DISABLE_KBD_INT ; 
 int KBD_DISABLE_KBD_PORT ; 
 int KBD_ENABLE_AUX_PORT ; 
 int KBD_KBD_CONTROL_BITS ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int PSM_VALID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_aux_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_aux_buffer (int /*<<< orphan*/ ,int) ; 
 int get_controller_command_byte (int /*<<< orphan*/ ) ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kbdc_get_device_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
psmclose(struct psm_softc *sc)
{
	int stat[3];
	int command_byte;
	int s;

	/* don't let timeout routines in the keyboard driver to poll the kbdc */
	if (!kbdc_lock(sc->kbdc, TRUE))
		return (EIO);

	/* save the current controller command byte */
	s = spltty();
	command_byte = get_controller_command_byte(sc->kbdc);
	if (command_byte == -1) {
		kbdc_lock(sc->kbdc, FALSE);
		splx(s);
		return (EIO);
	}

	/* disable the aux interrupt and temporalily disable the keyboard */
	if (!set_controller_command_byte(sc->kbdc,
	    kbdc_get_device_mask(sc->kbdc),
	    KBD_DISABLE_KBD_PORT | KBD_DISABLE_KBD_INT |
	    KBD_ENABLE_AUX_PORT | KBD_DISABLE_AUX_INT)) {
		log(LOG_ERR,
		    "psm%d: failed to disable the aux int (psmclose).\n",
		    sc->unit);
		/* CONTROLLER ERROR;
		 * NOTE: we shall force our way through. Because the only
		 * ill effect we shall see is that we may not be able
		 * to read ACK from the mouse, and it doesn't matter much
		 * so long as the mouse will accept the DISABLE command.
		 */
	}
	splx(s);

	/* stop the watchdog timer */
	callout_stop(&sc->callout);

	/* remove anything left in the output buffer */
	empty_aux_buffer(sc->kbdc, 10);

	/* disable the aux device, port and interrupt */
	if (sc->state & PSM_VALID) {
		if (!disable_aux_dev(sc->kbdc)) {
			/* MOUSE ERROR;
			 * NOTE: we don't return (error) and continue,
			 * pretending we have successfully disabled the device.
			 * It's OK because the interrupt routine will discard
			 * any data from the mouse hereafter.
			 */
			log(LOG_ERR,
			    "psm%d: failed to disable the device (psmclose).\n",
			    sc->unit);
		}

		if (get_mouse_status(sc->kbdc, stat, 0, 3) < 3)
			log(LOG_DEBUG,
			    "psm%d: failed to get status (psmclose).\n",
			    sc->unit);
	}

	if (!set_controller_command_byte(sc->kbdc,
	    kbdc_get_device_mask(sc->kbdc),
	    (command_byte & KBD_KBD_CONTROL_BITS) |
	    KBD_DISABLE_AUX_PORT | KBD_DISABLE_AUX_INT)) {
		/*
		 * CONTROLLER ERROR;
		 * we shall ignore this error; see the above comment.
		 */
		log(LOG_ERR,
		    "psm%d: failed to disable the aux port (psmclose).\n",
		    sc->unit);
	}

	/* remove anything left in the output buffer */
	empty_aux_buffer(sc->kbdc, 10);

	/* close is almost always successful */
	kbdc_lock(sc->kbdc, FALSE);
	return (0);
}