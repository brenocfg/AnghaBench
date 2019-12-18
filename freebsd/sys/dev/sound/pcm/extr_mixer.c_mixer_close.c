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
struct thread {int dummy; } ;
struct snddev_info {int dummy; } ;
struct snd_mixer {scalar_t__ busy; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct cdev {struct snd_mixer* si_drv1; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  PCM_REGISTERED (struct snddev_info*) ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mixer_close(struct cdev *i_dev, int flags, int mode, struct thread *td)
{
	struct snddev_info *d;
	struct snd_mixer *m;
	int ret;

	if (i_dev == NULL || i_dev->si_drv1 == NULL)
		return (EBADF);

	m = i_dev->si_drv1;
	d = device_get_softc(m->dev);
	if (!PCM_REGISTERED(d))
		return (EBADF);

	/* XXX Need Giant magic entry ??? */

	snd_mtxlock(m->lock);
	ret = (m->busy == 0) ? EBADF : 0;
	m->busy = 0;
	snd_mtxunlock(m->lock);

	return (ret);
}