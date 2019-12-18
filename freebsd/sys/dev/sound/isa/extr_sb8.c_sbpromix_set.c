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
typedef  unsigned int u_char ;
struct snd_mixer {int dummy; } ;
struct sb_info {int dummy; } ;

/* Variables and functions */
#define  SOUND_MIXER_CD 133 
#define  SOUND_MIXER_LINE 132 
#define  SOUND_MIXER_MIC 131 
#define  SOUND_MIXER_PCM 130 
#define  SOUND_MIXER_SYNTH 129 
#define  SOUND_MIXER_VOLUME 128 
 struct sb_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  sb_setmixer (struct sb_info*,int,unsigned int) ; 

__attribute__((used)) static int
sbpromix_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
    	struct sb_info *sb = mix_getdevinfo(m);
    	int reg, max;
    	u_char val;

	max = 7;
	switch (dev) {
	case SOUND_MIXER_PCM:
		reg = 0x04;
		break;

	case SOUND_MIXER_MIC:
		reg = 0x0a;
		max = 3;
		break;

	case SOUND_MIXER_VOLUME:
		reg = 0x22;
		break;

	case SOUND_MIXER_SYNTH:
		reg = 0x26;
		break;

	case SOUND_MIXER_CD:
		reg = 0x28;
		break;

	case SOUND_MIXER_LINE:
		reg = 0x2e;
		break;

	default:
		return -1;
	}

	left = (left * max) / 100;
	right = (dev == SOUND_MIXER_MIC)? left : ((right * max) / 100);

	val = (dev == SOUND_MIXER_MIC)? (left << 1) : (left << 5 | right << 1);
	sb_setmixer(sb, reg, val);

	left = (left * 100) / max;
	right = (right * 100) / max;

    	return left | (right << 8);
}