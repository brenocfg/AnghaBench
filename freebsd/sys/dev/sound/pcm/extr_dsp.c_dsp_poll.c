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
struct pcm_channel {int flags; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int CHN_F_DEAD ; 
 int /*<<< orphan*/  DSP_REGISTERED (struct snddev_info*,struct cdev*) ; 
 int EBADF ; 
 int /*<<< orphan*/  PCM_GIANT_ENTER (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_GIANT_LEAVE (struct snddev_info*) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int SD_F_PRIO_RD ; 
 int SD_F_PRIO_WR ; 
 int chn_poll (struct pcm_channel*,int,struct thread*) ; 
 struct snddev_info* dsp_get_info (struct cdev*) ; 
 int /*<<< orphan*/  getchns (struct cdev*,struct pcm_channel**,struct pcm_channel**,int) ; 
 int /*<<< orphan*/  relchns (struct cdev*,struct pcm_channel*,struct pcm_channel*,int) ; 

__attribute__((used)) static int
dsp_poll(struct cdev *i_dev, int events, struct thread *td)
{
	struct snddev_info *d;
	struct pcm_channel *wrch, *rdch;
	int ret, e;

	d = dsp_get_info(i_dev);
	if (!DSP_REGISTERED(d, i_dev))
		return (EBADF);

	PCM_GIANT_ENTER(d);

	wrch = NULL;
	rdch = NULL;
	ret = 0;

	getchns(i_dev, &rdch, &wrch, SD_F_PRIO_RD | SD_F_PRIO_WR);

	if (wrch != NULL && !(wrch->flags & CHN_F_DEAD)) {
		e = (events & (POLLOUT | POLLWRNORM));
		if (e)
			ret |= chn_poll(wrch, e, td);
	}

	if (rdch != NULL && !(rdch->flags & CHN_F_DEAD)) {
		e = (events & (POLLIN | POLLRDNORM));
		if (e)
			ret |= chn_poll(rdch, e, td);
	}

	relchns(i_dev, rdch, wrch, SD_F_PRIO_RD | SD_F_PRIO_WR);

	PCM_GIANT_LEAVE(d);

	return (ret);
}