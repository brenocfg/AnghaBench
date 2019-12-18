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
typedef  int u_int32_t ;
struct snddev_info {int flags; } ;
struct snd_mixer {int recdevs; int recsrc; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MIXER_SETRECSRC (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  MIXER_SET_LOCK (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  MIXER_SET_UNLOCK (struct snd_mixer*,int) ; 
 int SD_F_MPSAFE ; 
 int SOUND_MASK_LINE ; 
 int SOUND_MASK_MIC ; 
 int SOUND_MASK_MONITOR ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int ffs (int) ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mixer_setrecsrc(struct snd_mixer *mixer, u_int32_t src)
{
	struct snddev_info *d;
	u_int32_t recsrc;
	int dropmtx;

	d = device_get_softc(mixer->dev);
	if (d == NULL)
		return -1;
	if (!(d->flags & SD_F_MPSAFE) && mtx_owned(mixer->lock) != 0)
		dropmtx = 1;
	else
		dropmtx = 0;
	src &= mixer->recdevs;
	if (src == 0)
		src = mixer->recdevs & SOUND_MASK_MIC;
	if (src == 0)
		src = mixer->recdevs & SOUND_MASK_MONITOR;
	if (src == 0)
		src = mixer->recdevs & SOUND_MASK_LINE;
	if (src == 0 && mixer->recdevs != 0)
		src = (1 << (ffs(mixer->recdevs) - 1));
	/* It is safe to drop this mutex due to Giant. */
	MIXER_SET_UNLOCK(mixer, dropmtx);
	recsrc = MIXER_SETRECSRC(mixer, src);
	MIXER_SET_LOCK(mixer, dropmtx);

	mixer->recsrc = recsrc;

	return 0;
}