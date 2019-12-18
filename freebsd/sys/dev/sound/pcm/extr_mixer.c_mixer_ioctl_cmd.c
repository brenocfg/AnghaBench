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
typedef  int u_long ;
struct thread {int dummy; } ;
struct snd_mixer {int /*<<< orphan*/  lock; int /*<<< orphan*/  enuminfo; int /*<<< orphan*/  busy; } ;
struct cdev {struct snd_mixer* si_drv1; } ;
typedef  int /*<<< orphan*/  oss_sysinfo ;
typedef  int /*<<< orphan*/  oss_mixerinfo ;
typedef  int /*<<< orphan*/  oss_mixer_enuminfo ;
typedef  int /*<<< orphan*/  oss_card_info ;
typedef  int /*<<< orphan*/  oss_audioinfo ;
typedef  int /*<<< orphan*/  mixer_info ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int ENXIO ; 
 char IOCGROUP (int) ; 
 int MIXER_CMD_CDEV ; 
 int MIXER_READ (int /*<<< orphan*/ ) ; 
 int MIXER_WRITE (int /*<<< orphan*/ ) ; 
#define  OSS_GETVERSION 143 
#define  SNDCTL_AUDIOINFO 142 
#define  SNDCTL_AUDIOINFO_EX 141 
#define  SNDCTL_CARDINFO 140 
#define  SNDCTL_DSP_GET_RECSRC 139 
#define  SNDCTL_DSP_GET_RECSRC_NAMES 138 
#define  SNDCTL_DSP_SET_RECSRC 137 
#define  SNDCTL_ENGINEINFO 136 
#define  SNDCTL_MIXERINFO 135 
#define  SNDCTL_SYSINFO 134 
#define  SOUND_MIXER_CAPS 133 
#define  SOUND_MIXER_DEVMASK 132 
#define  SOUND_MIXER_INFO 131 
#define  SOUND_MIXER_RECMASK 130 
#define  SOUND_MIXER_RECSRC 129 
#define  SOUND_MIXER_STEREODEVS 128 
 int SOUND_VERSION ; 
 int /*<<< orphan*/  bcopy (void*,scalar_t__,int) ; 
 int dsp_oss_audioinfo (struct cdev*,int /*<<< orphan*/ *) ; 
 int mix_getdevs (struct snd_mixer*) ; 
 int mix_getrecdevs (struct snd_mixer*) ; 
 int mixer_get (struct snd_mixer*,int) ; 
 int mixer_get_recroute (struct snd_mixer*,int*) ; 
 int mixer_getrecsrc (struct snd_mixer*) ; 
 int /*<<< orphan*/  mixer_mixerinfo (struct snd_mixer*,int /*<<< orphan*/ *) ; 
 int mixer_oss_mixerinfo (struct cdev*,int /*<<< orphan*/ *) ; 
 int mixer_set (struct snd_mixer*,int,int) ; 
 int mixer_set_recroute (struct snd_mixer*,int) ; 
 int mixer_setrecsrc (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int sound_oss_card_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sound_oss_sysinfo (int /*<<< orphan*/ *) ; 

int
mixer_ioctl_cmd(struct cdev *i_dev, u_long cmd, caddr_t arg, int mode,
    struct thread *td, int from)
{
	struct snd_mixer *m;
	int ret = EINVAL, *arg_i = (int *)arg;
	int v = -1, j = cmd & 0xff;

	/*
	 * Certain ioctls may be made on any type of device (audio, mixer,
	 * and MIDI).  Handle those special cases here.
	 */
	if (IOCGROUP(cmd) == 'X') {
		switch (cmd) {
		case SNDCTL_SYSINFO:
			sound_oss_sysinfo((oss_sysinfo *)arg);
			return (0);
		case SNDCTL_CARDINFO:
			return (sound_oss_card_info((oss_card_info *)arg));
	    	case SNDCTL_AUDIOINFO:
	    	case SNDCTL_AUDIOINFO_EX:
	    	case SNDCTL_ENGINEINFO:
			return (dsp_oss_audioinfo(i_dev, (oss_audioinfo *)arg));
		case SNDCTL_MIXERINFO:
			return (mixer_oss_mixerinfo(i_dev, (oss_mixerinfo *)arg));
		}
		return (EINVAL);
	}

	m = i_dev->si_drv1;

	if (m == NULL)
		return (EBADF);

	snd_mtxlock(m->lock);
	if (from == MIXER_CMD_CDEV && !m->busy) {
		snd_mtxunlock(m->lock);
		return (EBADF);
	}
	switch (cmd) {
	case SNDCTL_DSP_GET_RECSRC_NAMES:
		bcopy((void *)&m->enuminfo, arg, sizeof(oss_mixer_enuminfo));
		ret = 0;
		goto done;
	case SNDCTL_DSP_GET_RECSRC:
		ret = mixer_get_recroute(m, arg_i);
		goto done;
	case SNDCTL_DSP_SET_RECSRC:
		ret = mixer_set_recroute(m, *arg_i);
		goto done;
	case OSS_GETVERSION:
		*arg_i = SOUND_VERSION;
		ret = 0;
		goto done;
	case SOUND_MIXER_INFO:
		mixer_mixerinfo(m, (mixer_info *)arg);
		ret = 0;
		goto done;
	}
	if ((cmd & ~0xff) == MIXER_WRITE(0)) {
		if (j == SOUND_MIXER_RECSRC)
			ret = mixer_setrecsrc(m, *arg_i);
		else
			ret = mixer_set(m, j, *arg_i);
		snd_mtxunlock(m->lock);
		return ((ret == 0) ? 0 : ENXIO);
	}
	if ((cmd & ~0xff) == MIXER_READ(0)) {
		switch (j) {
		case SOUND_MIXER_DEVMASK:
		case SOUND_MIXER_CAPS:
		case SOUND_MIXER_STEREODEVS:
			v = mix_getdevs(m);
			break;
		case SOUND_MIXER_RECMASK:
			v = mix_getrecdevs(m);
			break;
		case SOUND_MIXER_RECSRC:
			v = mixer_getrecsrc(m);
			break;
		default:
			v = mixer_get(m, j);
		}
		*arg_i = v;
		snd_mtxunlock(m->lock);
		return ((v != -1) ? 0 : ENXIO);
	}
done:
	snd_mtxunlock(m->lock);
	return (ret);
}