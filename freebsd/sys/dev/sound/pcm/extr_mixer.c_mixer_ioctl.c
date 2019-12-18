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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct snddev_info {int flags; } ;
struct snd_mixer {int /*<<< orphan*/  dev; } ;
struct cdev {int /*<<< orphan*/ * si_drv1; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  MIXER_CMD_CDEV ; 
 int /*<<< orphan*/  PCM_ACQUIRE_QUICK (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_GIANT_ENTER (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_GIANT_LEAVE (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_REGISTERED (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_RELEASE_QUICK (struct snddev_info*) ; 
 int SD_F_VPC ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ mixer_bypass ; 
 int mixer_ioctl_channel (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct thread*,int /*<<< orphan*/ ) ; 
 int mixer_ioctl_cmd (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mixer_ioctl(struct cdev *i_dev, u_long cmd, caddr_t arg, int mode,
    struct thread *td)
{
	struct snddev_info *d;
	int ret;

	if (i_dev == NULL || i_dev->si_drv1 == NULL)
		return (EBADF);

	d = device_get_softc(((struct snd_mixer *)i_dev->si_drv1)->dev);
	if (!PCM_REGISTERED(d))
		return (EBADF);

	PCM_GIANT_ENTER(d);
	PCM_ACQUIRE_QUICK(d);

	ret = -1;

	if (mixer_bypass != 0 && (d->flags & SD_F_VPC))
		ret = mixer_ioctl_channel(i_dev, cmd, arg, mode, td,
		    MIXER_CMD_CDEV);

	if (ret == -1)
		ret = mixer_ioctl_cmd(i_dev, cmd, arg, mode, td,
		    MIXER_CMD_CDEV);

	PCM_RELEASE_QUICK(d);
	PCM_GIANT_LEAVE(d);

	return (ret);
}