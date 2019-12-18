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
struct snd_mixer {int dummy; } ;
struct bcm2835_audio_info {unsigned int volume; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_AUDIO_LOCK (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  BCM2835_AUDIO_UNLOCK (struct bcm2835_audio_info*) ; 
#define  SOUND_MIXER_VOLUME 128 
 int /*<<< orphan*/  bcm2835_worker_update_params (struct bcm2835_audio_info*) ; 
 struct bcm2835_audio_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static int
bcmmix_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
    	struct bcm2835_audio_info *sc = mix_getdevinfo(m);

	switch (dev) {
	case SOUND_MIXER_VOLUME:
		BCM2835_AUDIO_LOCK(sc);
		sc->volume = left;
		bcm2835_worker_update_params(sc);
		BCM2835_AUDIO_UNLOCK(sc);

		break;

	default:
		break;
	}

    	return left | (left << 8);
}