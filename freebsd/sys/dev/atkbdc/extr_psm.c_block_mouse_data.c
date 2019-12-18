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
struct psm_softc {int /*<<< orphan*/  kbdc; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FALSE ; 
 int KBD_DISABLE_AUX_INT ; 
 int KBD_DISABLE_KBD_INT ; 
 int KBD_DISABLE_KBD_PORT ; 
 int KBD_ENABLE_AUX_PORT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  empty_aux_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushpackets (struct psm_softc*) ; 
 int get_controller_command_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_get_device_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_aux_data_no_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
block_mouse_data(struct psm_softc *sc, int *c)
{
	int s;

	if (!kbdc_lock(sc->kbdc, TRUE))
		return (EIO);

	s = spltty();
	*c = get_controller_command_byte(sc->kbdc);
	if ((*c == -1) || !set_controller_command_byte(sc->kbdc,
	    kbdc_get_device_mask(sc->kbdc),
	    KBD_DISABLE_KBD_PORT | KBD_DISABLE_KBD_INT |
	    KBD_ENABLE_AUX_PORT | KBD_DISABLE_AUX_INT)) {
		/* this is CONTROLLER ERROR */
		splx(s);
		kbdc_lock(sc->kbdc, FALSE);
		return (EIO);
	}

	/*
	 * The device may be in the middle of status data transmission.
	 * The transmission will be interrupted, thus, incomplete status
	 * data must be discarded. Although the aux interrupt is disabled
	 * at the keyboard controller level, at most one aux interrupt
	 * may have already been pending and a data byte is in the
	 * output buffer; throw it away. Note that the second argument
	 * to `empty_aux_buffer()' is zero, so that the call will just
	 * flush the internal queue.
	 * `psmintr()' will be invoked after `splx()' if an interrupt is
	 * pending; it will see no data and returns immediately.
	 */
	empty_aux_buffer(sc->kbdc, 0);		/* flush the queue */
	read_aux_data_no_wait(sc->kbdc);	/* throw away data if any */
	flushpackets(sc);
	splx(s);

	return (0);
}