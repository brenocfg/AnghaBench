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
struct snddev_info {int playcount; int reccount; scalar_t__ pvchancount; scalar_t__ rvchancount; int /*<<< orphan*/  clones; } ;

/* Variables and functions */
 int PCMMAXCLONE ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int max (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_clone_gc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_clone_setmaxunit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_maxautovchans ; 

__attribute__((used)) static void
pcm_clonereset(struct snddev_info *d)
{
	int cmax;

	PCM_BUSYASSERT(d);

	cmax = d->playcount + d->reccount - 1;
	if (d->pvchancount > 0)
		cmax += max(d->pvchancount, snd_maxautovchans) - 1;
	if (d->rvchancount > 0)
		cmax += max(d->rvchancount, snd_maxautovchans) - 1;
	if (cmax > PCMMAXCLONE)
		cmax = PCMMAXCLONE;
	(void)snd_clone_gc(d->clones);
	(void)snd_clone_setmaxunit(d->clones, cmax);
}