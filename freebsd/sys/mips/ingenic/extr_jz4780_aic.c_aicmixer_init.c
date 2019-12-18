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
struct sc_pcminfo {int /*<<< orphan*/  dev; struct aic_softc* sc; } ;
struct aic_softc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int SD_F_SOFTPCMVOL ; 
 int SOUND_MASK_PCM ; 
 struct sc_pcminfo* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aicmixer_init(struct snd_mixer *m)
{
	struct sc_pcminfo *scp;
	struct aic_softc *sc;
	int mask;

	scp = mix_getdevinfo(m);
	sc = scp->sc;

	if (sc == NULL)
		return -1;

	mask = SOUND_MASK_PCM;

	snd_mtxlock(sc->lock);
	pcm_setflags(scp->dev, pcm_getflags(scp->dev) | SD_F_SOFTPCMVOL);
	mix_setdevs(m, mask);
	snd_mtxunlock(sc->lock);

	return (0);
}