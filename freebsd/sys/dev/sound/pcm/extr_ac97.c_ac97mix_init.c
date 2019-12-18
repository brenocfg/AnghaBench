#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct snd_mixer {int dummy; } ;
struct ac97_info {int id; TYPE_1__* mix; int /*<<< orphan*/  dev; int /*<<< orphan*/  subvendor; } ;
struct TYPE_2__ {int enable; scalar_t__ recidx; } ;

/* Variables and functions */
 size_t AC97_MIXER_SIZE ; 
 int /*<<< orphan*/  AC97_MIX_MASTER ; 
 int /*<<< orphan*/  AC97_MIX_PCM ; 
 int SD_F_SOFTPCMVOL ; 
 size_t SOUND_MASK_CD ; 
 size_t SOUND_MASK_OGAIN ; 
 size_t SOUND_MASK_PCM ; 
 size_t SOUND_MASK_PHONEOUT ; 
 size_t SOUND_MIXER_NONE ; 
 size_t SOUND_MIXER_OGAIN ; 
 size_t SOUND_MIXER_PCM ; 
 size_t SOUND_MIXER_PHONEOUT ; 
 size_t SOUND_MIXER_VOLUME ; 
 int /*<<< orphan*/  ac97_init_sysctl (struct ac97_info*) ; 
 scalar_t__ ac97_initmixer (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 struct ac97_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,size_t) ; 
 int /*<<< orphan*/  mix_setparentchild (struct snd_mixer*,size_t,size_t) ; 
 int /*<<< orphan*/  mix_setrealdev (struct snd_mixer*,size_t,size_t) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,size_t) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ac97mix_init(struct snd_mixer *m)
{
	struct ac97_info *codec = mix_getdevinfo(m);
	u_int32_t i, mask;

	if (codec == NULL)
		return -1;

	if (ac97_initmixer(codec))
		return -1;

	switch (codec->id) {
	case 0x41445374:	/* AD1981B */
		switch (codec->subvendor) {
		case 0x02d91014:
			/*
			 * IBM Thinkcentre:
			 *
			 * Tie "ogain" and "phout" to "vol" since its
			 * master volume is basically useless and can't
			 * control anything.
			 */
			mask = 0;
			if (codec->mix[SOUND_MIXER_OGAIN].enable)
				mask |= SOUND_MASK_OGAIN;
			if (codec->mix[SOUND_MIXER_PHONEOUT].enable)
				mask |= SOUND_MASK_PHONEOUT;
			if (codec->mix[SOUND_MIXER_VOLUME].enable)
				mix_setparentchild(m, SOUND_MIXER_VOLUME,
				    mask);
			else {
				mix_setparentchild(m, SOUND_MIXER_VOLUME,
				    mask);
				mix_setrealdev(m, SOUND_MIXER_VOLUME,
				    SOUND_MIXER_NONE);
			}
			break;
		case 0x099c103c:
			/*
			 * HP nx6110:
			 *
			 * By default, "vol" is controlling internal speakers
			 * (not a master volume!) and "ogain" is controlling
			 * headphone. Enable dummy "phout" so it can be
			 * remapped to internal speakers and virtualize
			 * "vol" to control both.
			 */
			codec->mix[SOUND_MIXER_OGAIN].enable = 1;
			codec->mix[SOUND_MIXER_PHONEOUT].enable = 1;
			mix_setrealdev(m, SOUND_MIXER_PHONEOUT,
			    SOUND_MIXER_VOLUME);
			mix_setrealdev(m, SOUND_MIXER_VOLUME,
			    SOUND_MIXER_NONE);
			mix_setparentchild(m, SOUND_MIXER_VOLUME,
			    SOUND_MASK_OGAIN | SOUND_MASK_PHONEOUT);
			break;
		default:
			break;
		}
		break;
	case 0x434d4941:	/* CMI9738 */
	case 0x434d4961:	/* CMI9739 */
	case 0x434d4978:	/* CMI9761 */
	case 0x434d4982:	/* CMI9761 */
	case 0x434d4983:	/* CMI9761 */
		bzero(&codec->mix[SOUND_MIXER_PCM],
		    sizeof(codec->mix[SOUND_MIXER_PCM]));
		pcm_setflags(codec->dev, pcm_getflags(codec->dev) |
		    SD_F_SOFTPCMVOL);
		/* XXX How about master volume ? */
		break;
	default:
		break;
	}

	if (pcm_getflags(codec->dev) & SD_F_SOFTPCMVOL)
		ac97_wrcd(codec, AC97_MIX_PCM, 0);
#if 0
	/* XXX For the sake of debugging purposes */
	mix_setparentchild(m, SOUND_MIXER_VOLUME,
	    SOUND_MASK_PCM | SOUND_MASK_CD);
	mix_setrealdev(m, SOUND_MIXER_VOLUME, SOUND_MIXER_NONE);
	ac97_wrcd(codec, AC97_MIX_MASTER, 0);
#endif

	mask = 0;
	for (i = 0; i < AC97_MIXER_SIZE; i++)
		mask |= codec->mix[i].enable? 1 << i : 0;
	mix_setdevs(m, mask);

	mask = 0;
	for (i = 0; i < AC97_MIXER_SIZE; i++)
		mask |= codec->mix[i].recidx? 1 << i : 0;
	mix_setrecdevs(m, mask);

	ac97_init_sysctl(codec);

	return 0;
}