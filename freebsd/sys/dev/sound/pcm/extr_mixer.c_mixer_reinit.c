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
struct snd_mixer {int /*<<< orphan*/  lock; int /*<<< orphan*/  recsrc; int /*<<< orphan*/ * level; } ;
struct cdev {struct snd_mixer* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MIXER_REINIT (struct snd_mixer*) ; 
 int SOUND_MIXER_NRDEVICES ; 
 struct cdev* mixer_get_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_set (struct snd_mixer*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_setrecsrc (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

int
mixer_reinit(device_t dev)
{
	struct snd_mixer *m;
	struct cdev *pdev;
	int i;

	pdev = mixer_get_devt(dev);
	m = pdev->si_drv1;
	snd_mtxlock(m->lock);

	i = MIXER_REINIT(m);
	if (i) {
		snd_mtxunlock(m->lock);
		return i;
	}

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
		mixer_set(m, i, m->level[i]);

	mixer_setrecsrc(m, m->recsrc);
	snd_mtxunlock(m->lock);

	return 0;
}