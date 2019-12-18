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
struct uaudio_chan {scalar_t__ running; struct uaudio_softc* priv_sc; } ;
struct uaudio_softc {int /*<<< orphan*/  sc_udev; struct uaudio_chan sc_play_chan; struct uaudio_chan sc_rec_chan; } ;

/* Variables and functions */
 scalar_t__ uaudio_chan_need_both (struct uaudio_softc*) ; 
 scalar_t__ uaudio_chan_need_none (struct uaudio_softc*) ; 
 int /*<<< orphan*/  uaudio_chan_stop_sub (struct uaudio_chan*) ; 
 int /*<<< orphan*/  usb_proc_explore_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_explore_unlock (int /*<<< orphan*/ ) ; 

void
uaudio_chan_stop(struct uaudio_chan *ch)
{
	struct uaudio_softc *sc = ch->priv_sc;

	/* make operation atomic */
	usb_proc_explore_lock(sc->sc_udev);

	/* check if running */
	if (ch->running != 0) {
		/* clear running flag */
		ch->running = 0;

		if (uaudio_chan_need_both(sc)) {
			/*
			 * Leave the endpoints running because we need
			 * information about jitter!
			 */
		} else if (uaudio_chan_need_none(sc)) {
			/*
			 * Stop both endpoints in case the one was used for
			 * jitter information:
			 */
			uaudio_chan_stop_sub(&sc->sc_rec_chan);
			uaudio_chan_stop_sub(&sc->sc_play_chan);
		} else {
			uaudio_chan_stop_sub(ch);
		}
	}

	/* exit atomic operation */
	usb_proc_explore_unlock(sc->sc_udev);
}