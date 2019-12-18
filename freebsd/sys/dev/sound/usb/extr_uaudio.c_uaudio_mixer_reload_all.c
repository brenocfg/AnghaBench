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
struct TYPE_2__ {int /*<<< orphan*/ * xfer; } ;
struct uaudio_softc {int /*<<< orphan*/ * sc_mixer_lock; TYPE_1__ sc_hid; int /*<<< orphan*/ * sc_mixer_xfer; struct uaudio_mixer_node* sc_mixer_root; } ;
struct uaudio_mixer_node {scalar_t__ ctl; int nchan; int* update; struct uaudio_mixer_node* next; } ;

/* Variables and functions */
 scalar_t__ SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uaudio_mixer_reload_all(struct uaudio_softc *sc)
{
	struct uaudio_mixer_node *pmc;
	int chan;

	if (sc->sc_mixer_lock == NULL)
		return;

	mtx_lock(sc->sc_mixer_lock);
	for (pmc = sc->sc_mixer_root; pmc != NULL; pmc = pmc->next) {
		/* use reset defaults for non-oss controlled settings */
		if (pmc->ctl == SOUND_MIXER_NRDEVICES)
			continue;
		for (chan = 0; chan < pmc->nchan; chan++)
			pmc->update[chan / 8] |= (1 << (chan % 8));
	}
	usbd_transfer_start(sc->sc_mixer_xfer[0]);

	/* start HID volume keys, if any */
	usbd_transfer_start(sc->sc_hid.xfer[0]);
	mtx_unlock(sc->sc_mixer_lock);
}