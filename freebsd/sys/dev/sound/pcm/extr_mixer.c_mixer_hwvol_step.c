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
struct snd_mixer {int /*<<< orphan*/  lock; } ;
struct cdev {struct snd_mixer* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct cdev* mixer_get_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_hwvol_step_locked (struct snd_mixer*,int,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

void
mixer_hwvol_step(device_t dev, int left_step, int right_step)
{
	struct snd_mixer *m;
	struct cdev *pdev;

	pdev = mixer_get_devt(dev);
	m = pdev->si_drv1;
	snd_mtxlock(m->lock);
	mixer_hwvol_step_locked(m, left_step, right_step);
	snd_mtxunlock(m->lock);
}