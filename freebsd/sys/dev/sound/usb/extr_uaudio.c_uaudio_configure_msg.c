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
struct usb_proc_msg {int dummy; } ;
struct uaudio_softc {int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_rec_chan; int /*<<< orphan*/  sc_play_chan; } ;
struct uaudio_configure_msg {struct uaudio_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  uaudio_configure_msg_sub (struct uaudio_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_explore_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_explore_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uaudio_configure_msg(struct usb_proc_msg *pm)
{
	struct uaudio_softc *sc = ((struct uaudio_configure_msg *)pm)->sc;

	usb_proc_explore_unlock(sc->sc_udev);
	uaudio_configure_msg_sub(sc, &sc->sc_play_chan, PCMDIR_PLAY);
	uaudio_configure_msg_sub(sc, &sc->sc_rec_chan, PCMDIR_REC);
	usb_proc_explore_lock(sc->sc_udev);
}