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
struct snd_mixer {int dummy; } ;
struct emu_pcm_info {scalar_t__ route; int ac97_playdevs; int ac97_recdevs; scalar_t__ is_emu10k1; int /*<<< orphan*/ * sm; int /*<<< orphan*/ * codec; int /*<<< orphan*/ * ac97_mixerclass; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ recdev; scalar_t__ present; } ;
struct TYPE_3__ {scalar_t__ recdev; scalar_t__ present; } ;

/* Variables and functions */
 scalar_t__ RT_FRONT ; 
 int SOUND_MIXER_NRDEVICES ; 
 int SOUND_MIXER_PCM ; 
 int SOUND_MIXER_VOLUME ; 
 TYPE_2__* dspmix_k1 ; 
 TYPE_1__* dspmix_k2 ; 
 struct emu_pcm_info* mix_getdevinfo (struct snd_mixer*) ; 
 int mix_getdevs (int /*<<< orphan*/ *) ; 
 int mix_getrecdevs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,int) ; 
 int /*<<< orphan*/ * mixer_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
emu_dspmixer_init(struct snd_mixer *m)
{
	struct emu_pcm_info	*sc;
	int i;
	int p, r;

	p = 0;
	r = 0;

	sc = mix_getdevinfo(m);

	if (sc->route == RT_FRONT) {
		/* create submixer for AC97 codec */
		if ((sc->ac97_mixerclass != NULL) && (sc->codec != NULL)) {
			sc->sm = mixer_create(sc->dev, sc->ac97_mixerclass, sc->codec, "ac97");
			if (sc->sm != NULL) {
				p = mix_getdevs(sc->sm);
				r = mix_getrecdevs(sc->sm);
			}
		}

		sc->ac97_playdevs = p;
		sc->ac97_recdevs = r;
	}

	/* This two are always here */
	p |= (1 << SOUND_MIXER_PCM);
	p |= (1 << SOUND_MIXER_VOLUME);

	if (sc->route == RT_FRONT) {
		if (sc->is_emu10k1) {
			for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
				if (dspmix_k1[i].present)
					p |= (1 << i);
				if (dspmix_k1[i].recdev)
					r |= (1 << i);
			}
		} else {
			for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
				if (dspmix_k2[i].present)
					p |= (1 << i);
				if (dspmix_k2[i].recdev)
					r |= (1 << i);
			}
		}
	}

	mix_setdevs(m, p);
	mix_setrecdevs(m, r);

	return (0);
}