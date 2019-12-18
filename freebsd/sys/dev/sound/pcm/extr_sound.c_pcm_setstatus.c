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
struct snddev_info {int flags; scalar_t__ playcount; scalar_t__ reccount; int /*<<< orphan*/ * clones; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_LOCK (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_RELEASE (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_UNLOCK (struct snddev_info*) ; 
 int SD_F_AUTOVCHAN ; 
 int SD_F_REGISTERED ; 
 int SD_F_SIMPLEX ; 
 int /*<<< orphan*/  SND_STATUSLEN ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_best_unit (scalar_t__) ; 
 int /*<<< orphan*/  pcm_setmaxautovchans (struct snddev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_sysinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_clone_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_maxautovchans ; 
 scalar_t__ snd_unit ; 
 int snd_unit_auto ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
pcm_setstatus(device_t dev, char *str)
{
	struct snddev_info *d = device_get_softc(dev);

	/* should only be called once */
	if (d->flags & SD_F_REGISTERED)
		return (EINVAL);

	PCM_BUSYASSERT(d);

	if (d->playcount == 0 || d->reccount == 0)
		d->flags |= SD_F_SIMPLEX;

	if (d->playcount > 0 || d->reccount > 0)
		d->flags |= SD_F_AUTOVCHAN;

	pcm_setmaxautovchans(d, snd_maxautovchans);

	strlcpy(d->status, str, SND_STATUSLEN);

	PCM_LOCK(d);

	/* Last stage, enable cloning. */
	if (d->clones != NULL)
		(void)snd_clone_enable(d->clones);

	/* Done, we're ready.. */
	d->flags |= SD_F_REGISTERED;

	PCM_RELEASE(d);

	PCM_UNLOCK(d);

	/*
	 * Create all sysctls once SD_F_REGISTERED is set else
	 * tunable sysctls won't work:
	 */
	pcm_sysinit(dev);

	if (snd_unit_auto < 0)
		snd_unit_auto = (snd_unit < 0) ? 1 : 0;
	if (snd_unit < 0 || snd_unit_auto > 1)
		snd_unit = device_get_unit(dev);
	else if (snd_unit_auto == 1)
		snd_unit = pcm_best_unit(snd_unit);

	return (0);
}