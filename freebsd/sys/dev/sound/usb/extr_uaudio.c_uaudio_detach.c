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
struct TYPE_4__ {int /*<<< orphan*/  xfer; void* operation; } ;
struct TYPE_3__ {int /*<<< orphan*/  xfer; void* operation; } ;
struct uaudio_softc {scalar_t__ sc_sndstat_valid; int /*<<< orphan*/  sc_sndstat; TYPE_2__ sc_rec_chan; TYPE_1__ sc_play_chan; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/ * sc_config_msg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* CHAN_OP_DRAIN ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ UAUDIO_NCHANBUFS ; 
 scalar_t__ bus_generic_detach (int /*<<< orphan*/ ) ; 
 struct uaudio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uaudio_hid_detach (struct uaudio_softc*) ; 
 int /*<<< orphan*/  uaudio_mixer_ctl_free (struct uaudio_softc*) ; 
 int /*<<< orphan*/  umidi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_explore_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_explore_mwait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_explore_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
uaudio_detach(device_t dev)
{
	struct uaudio_softc *sc = device_get_softc(dev);

	/*
	 * Stop USB transfers early so that any audio applications
	 * will time out and close opened /dev/dspX.Y device(s), if
	 * any.
	 */
	usb_proc_explore_lock(sc->sc_udev);
	sc->sc_play_chan.operation = CHAN_OP_DRAIN;
	sc->sc_rec_chan.operation = CHAN_OP_DRAIN;
	usb_proc_explore_mwait(sc->sc_udev,
	    &sc->sc_config_msg[0], &sc->sc_config_msg[1]);
	usb_proc_explore_unlock(sc->sc_udev);

	usbd_transfer_unsetup(sc->sc_play_chan.xfer, UAUDIO_NCHANBUFS + 1);
	usbd_transfer_unsetup(sc->sc_rec_chan.xfer, UAUDIO_NCHANBUFS + 1);

	uaudio_hid_detach(sc);

	if (bus_generic_detach(dev) != 0) {
		DPRINTF("detach failed!\n");
	}
	sbuf_delete(&sc->sc_sndstat);
	sc->sc_sndstat_valid = 0;

	umidi_detach(dev);

	/* free mixer data */

	uaudio_mixer_ctl_free(sc);

	return (0);
}