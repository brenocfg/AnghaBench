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
struct snddev_info {int dummy; } ;
struct pcm_channel {int feederflags; scalar_t__ direction; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int CHN_GETVOLUME (struct pcm_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHN_LOCK (struct pcm_channel*) ; 
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
 int EINVAL ; 
 int FEEDER_VOLUME ; 
 int MIXER_READ (int /*<<< orphan*/ ) ; 
 int MIXER_WRITE (int /*<<< orphan*/ ) ; 
 int PCMDEV (struct cdev*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ PCMDIR_REC ; 
 struct pcm_channel* PCM_RDCH (struct cdev*) ; 
 int /*<<< orphan*/  PCM_REGISTERED (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_UNLOCKASSERT (struct snddev_info*) ; 
 struct pcm_channel* PCM_VOLCH (struct cdev*) ; 
 struct pcm_channel* PCM_WRCH (struct cdev*) ; 
 int SD_F_VPC ; 
 int /*<<< orphan*/  SND_CHN_T_FL ; 
 int /*<<< orphan*/  SND_CHN_T_FR ; 
 int SND_DEV_DSPHW_PLAY ; 
 int SND_DEV_DSPHW_REC ; 
 int SND_DEV_DSPHW_VPLAY ; 
 int SND_DEV_DSPHW_VREC ; 
 int /*<<< orphan*/  SND_VOL_C_PCM ; 
 int SOUND_MASK_PCM ; 
 int SOUND_MASK_RECLEV ; 
#define  SOUND_MIXER_CAPS 132 
#define  SOUND_MIXER_DEVMASK 131 
 int SOUND_MIXER_PCM ; 
 int SOUND_MIXER_RECLEV ; 
#define  SOUND_MIXER_RECMASK 130 
#define  SOUND_MIXER_RECSRC 129 
#define  SOUND_MIXER_STEREODEVS 128 
 int /*<<< orphan*/  chn_setvolume_multi (struct pcm_channel*,int /*<<< orphan*/ ,int,int,int) ; 
 int dsp_get_flags (struct cdev*) ; 
 struct snddev_info* dsp_get_info (struct cdev*) ; 
 int dsp_get_volume_channel (struct cdev*,struct pcm_channel**) ; 

__attribute__((used)) static int
dsp_ioctl_channel(struct cdev *dev, struct pcm_channel *volch, u_long cmd,
    caddr_t arg)
{
	struct snddev_info *d;
	struct pcm_channel *rdch, *wrch;
	int j, devtype, ret;

	d = dsp_get_info(dev);
	if (!PCM_REGISTERED(d) || !(dsp_get_flags(dev) & SD_F_VPC))
		return (-1);

	PCM_UNLOCKASSERT(d);

	j = cmd & 0xff;

	rdch = PCM_RDCH(dev);
	wrch = PCM_WRCH(dev);

	/* No specific channel, look into cache */
	if (volch == NULL)
		volch = PCM_VOLCH(dev);

	/* Look harder */
	if (volch == NULL) {
		if (j == SOUND_MIXER_RECLEV && rdch != NULL)
			volch = rdch;
		else if (j == SOUND_MIXER_PCM && wrch != NULL)
			volch = wrch;
	}

	devtype = PCMDEV(dev);

	/* Look super harder */
	if (volch == NULL &&
	    (devtype == SND_DEV_DSPHW_PLAY || devtype == SND_DEV_DSPHW_VPLAY ||
	    devtype == SND_DEV_DSPHW_REC || devtype == SND_DEV_DSPHW_VREC)) {
		ret = dsp_get_volume_channel(dev, &volch);
		if (ret != 0)
			return (ret);
		if (volch == NULL)
			return (EINVAL);
	}

	/* Final validation */
	if (volch != NULL) {
		CHN_LOCK(volch);
		if (!(volch->feederflags & (1 << FEEDER_VOLUME))) {
			CHN_UNLOCK(volch);
			return (-1);
		}
		if (volch->direction == PCMDIR_PLAY)
			wrch = volch;
		else
			rdch = volch;
	}

	ret = EINVAL;

	if (volch != NULL &&
	    ((j == SOUND_MIXER_PCM && volch->direction == PCMDIR_PLAY) ||
	    (j == SOUND_MIXER_RECLEV && volch->direction == PCMDIR_REC))) {
		if ((cmd & ~0xff) == MIXER_WRITE(0)) {
			int left, right, center;

			left = *(int *)arg & 0x7f;
			right = ((*(int *)arg) >> 8) & 0x7f;
			center = (left + right) >> 1;
			chn_setvolume_multi(volch, SND_VOL_C_PCM, left, right,
			    center);
		} else if ((cmd & ~0xff) == MIXER_READ(0)) {
			*(int *)arg = CHN_GETVOLUME(volch,
				SND_VOL_C_PCM, SND_CHN_T_FL);
			*(int *)arg |= CHN_GETVOLUME(volch,
				SND_VOL_C_PCM, SND_CHN_T_FR) << 8;
		}
		ret = 0;
	} else if (rdch != NULL || wrch != NULL) {
		switch (j) {
		case SOUND_MIXER_DEVMASK:
		case SOUND_MIXER_CAPS:
		case SOUND_MIXER_STEREODEVS:
			if ((cmd & ~0xff) == MIXER_READ(0)) {
				*(int *)arg = 0;
				if (rdch != NULL)
					*(int *)arg |= SOUND_MASK_RECLEV;
				if (wrch != NULL)
					*(int *)arg |= SOUND_MASK_PCM;
			}
			ret = 0;
			break;
		case SOUND_MIXER_RECMASK:
		case SOUND_MIXER_RECSRC:
			if ((cmd & ~0xff) == MIXER_READ(0))
				*(int *)arg = 0;
			ret = 0;
			break;
		default:
			break;
		}
	}

	if (volch != NULL)
		CHN_UNLOCK(volch);

	return (ret);
}