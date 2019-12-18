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
struct uaudio_softc {scalar_t__ sc_mixer_init; scalar_t__ sc_pcm_registered; int /*<<< orphan*/  (* sc_set_spdif_fn ) (struct uaudio_softc*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct uaudio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int mixer_uninit (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct uaudio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

int
uaudio_detach_sub(device_t dev)
{
	struct uaudio_softc *sc = device_get_softc(device_get_parent(dev));
	int error = 0;

	/* disable S/PDIF output, if any */
	(void) sc->sc_set_spdif_fn(sc, 0);

repeat:
	if (sc->sc_pcm_registered) {
		error = pcm_unregister(dev);
	} else {
		if (sc->sc_mixer_init) {
			error = mixer_uninit(dev);
		}
	}

	if (error) {
		device_printf(dev, "Waiting for sound application to exit!\n");
		usb_pause_mtx(NULL, 2 * hz);
		goto repeat;		/* try again */
	}
	return (0);			/* success */
}