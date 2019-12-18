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
struct uaudio_softc {int sc_mix_info; int /*<<< orphan*/  sc_recsrc_info; int /*<<< orphan*/  sc_mixer_lock; int /*<<< orphan*/  sc_mixer_xfer; int /*<<< orphan*/  sc_mixer_iface_index; int /*<<< orphan*/  sc_udev; struct snd_mixer* sc_mixer_dev; } ;
struct snd_mixer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SOUND_MASK_PCM ; 
 int SOUND_MASK_VOLUME ; 
 int /*<<< orphan*/  SOUND_MIXER_NONE ; 
 int /*<<< orphan*/  SOUND_MIXER_VOLUME ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  mix_setparentchild (struct snd_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_setrealdev (struct snd_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_get_lock (struct snd_mixer*) ; 
 int /*<<< orphan*/  uaudio_mixer_config ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct uaudio_softc*,int /*<<< orphan*/ ) ; 

int
uaudio_mixer_init_sub(struct uaudio_softc *sc, struct snd_mixer *m)
{
	DPRINTF("\n");

	sc->sc_mixer_lock = mixer_get_lock(m);
	sc->sc_mixer_dev = m;

	if (usbd_transfer_setup(sc->sc_udev, &sc->sc_mixer_iface_index,
	    sc->sc_mixer_xfer, uaudio_mixer_config, 1, sc,
	    sc->sc_mixer_lock)) {
		DPRINTFN(0, "could not allocate USB "
		    "transfer for audio mixer!\n");
		return (ENOMEM);
	}
	if (!(sc->sc_mix_info & SOUND_MASK_VOLUME)) {
		mix_setparentchild(m, SOUND_MIXER_VOLUME, SOUND_MASK_PCM);
		mix_setrealdev(m, SOUND_MIXER_VOLUME, SOUND_MIXER_NONE);
	}
	mix_setdevs(m, sc->sc_mix_info);
	mix_setrecdevs(m, sc->sc_recsrc_info);
	return (0);
}