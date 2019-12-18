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
struct TYPE_4__ {scalar_t__ num_alt; int /*<<< orphan*/  feedback_rate; } ;
struct TYPE_3__ {scalar_t__ num_alt; } ;
struct uaudio_softc {int sc_mix_info; int sc_mixer_init; int sc_pcm_registered; TYPE_2__ sc_play_chan; TYPE_1__ sc_rec_chan; scalar_t__ sc_pcm_bitperfect; scalar_t__ sc_uq_audio_swap_lr; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 char* PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_F_BITPERFECT ; 
 int /*<<< orphan*/  SD_F_MPSAFE ; 
 int /*<<< orphan*/  SD_F_SOFTPCMVOL ; 
 int SND_STATUSLEN ; 
 int SOUND_MASK_PCM ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct uaudio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_hwvol_init (int /*<<< orphan*/ ) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uaudio_softc*) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uaudio_softc*) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct uaudio_softc*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_uaudio ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  uaudio_detach_sub (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uaudio_mixer_init (struct uaudio_softc*) ; 
 int /*<<< orphan*/  uaudio_mixer_register_sysctl (struct uaudio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uaudio_pcm_setflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
uaudio_attach_sub(device_t dev, kobj_class_t mixer_class, kobj_class_t chan_class)
{
	struct uaudio_softc *sc = device_get_softc(device_get_parent(dev));
	char status[SND_STATUSLEN];

	uaudio_mixer_init(sc);

	if (sc->sc_uq_audio_swap_lr) {
		DPRINTF("hardware has swapped left and right\n");
		/* uaudio_pcm_setflags(dev, SD_F_PSWAPLR); */
	}
	if (!(sc->sc_mix_info & SOUND_MASK_PCM)) {

		DPRINTF("emulating master volume\n");

		/*
		 * Emulate missing pcm mixer controller
		 * through FEEDER_VOLUME
		 */
		uaudio_pcm_setflags(dev, SD_F_SOFTPCMVOL);
	}
	if (sc->sc_pcm_bitperfect) {
		DPRINTF("device needs bitperfect by default\n");
		uaudio_pcm_setflags(dev, SD_F_BITPERFECT);
	}
	if (mixer_init(dev, mixer_class, sc))
		goto detach;
	sc->sc_mixer_init = 1;

	mixer_hwvol_init(dev);

	snprintf(status, sizeof(status), "at ? %s", PCM_KLDSTRING(snd_uaudio));

	if (pcm_register(dev, sc,
	    (sc->sc_play_chan.num_alt > 0) ? 1 : 0,
	    (sc->sc_rec_chan.num_alt > 0) ? 1 : 0)) {
		goto detach;
	}

	uaudio_pcm_setflags(dev, SD_F_MPSAFE);
	sc->sc_pcm_registered = 1;

	if (sc->sc_play_chan.num_alt > 0) {
		pcm_addchan(dev, PCMDIR_PLAY, chan_class, sc);
	}
	if (sc->sc_rec_chan.num_alt > 0) {
		pcm_addchan(dev, PCMDIR_REC, chan_class, sc);
	}
	pcm_setstatus(dev, status);

	uaudio_mixer_register_sysctl(sc, dev);

	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "feedback_rate", CTLFLAG_RD, &sc->sc_play_chan.feedback_rate,
	    0, "Feedback sample rate in Hz");

	return (0);			/* success */

detach:
	uaudio_detach_sub(dev);
	return (ENXIO);
}