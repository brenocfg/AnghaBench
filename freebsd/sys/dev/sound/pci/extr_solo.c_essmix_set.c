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
struct snd_mixer {int dummy; } ;
struct ess_info {int dummy; } ;

/* Variables and functions */
#define  SOUND_MIXER_CD 134 
#define  SOUND_MIXER_LINE 133 
#define  SOUND_MIXER_LINE1 132 
#define  SOUND_MIXER_MIC 131 
#define  SOUND_MIXER_PCM 130 
#define  SOUND_MIXER_SYNTH 129 
#define  SOUND_MIXER_VOLUME 128 
 int /*<<< orphan*/  ess_setmixer (struct ess_info*,int,int) ; 
 struct ess_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static int
essmix_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
    	struct ess_info *sc = mix_getdevinfo(m);
    	int preg = 0, rreg = 0, l, r;

	l = (left * 15) / 100;
	r = (right * 15) / 100;
	switch (dev) {
	case SOUND_MIXER_SYNTH:
		preg = 0x36;
		rreg = 0x6b;
		break;

	case SOUND_MIXER_PCM:
		preg = 0x14;
		rreg = 0x7c;
		break;

	case SOUND_MIXER_LINE:
		preg = 0x3e;
		rreg = 0x6e;
		break;

	case SOUND_MIXER_MIC:
		preg = 0x1a;
		rreg = 0x68;
		break;

	case SOUND_MIXER_LINE1:
		preg = 0x3a;
		rreg = 0x6c;
		break;

	case SOUND_MIXER_CD:
		preg = 0x38;
		rreg = 0x6a;
		break;

	case SOUND_MIXER_VOLUME:
		l = left? (left * 63) / 100 : 64;
		r = right? (right * 63) / 100 : 64;
		ess_setmixer(sc, 0x60, l);
		ess_setmixer(sc, 0x62, r);
		left = (l == 64)? 0 : (l * 100) / 63;
		right = (r == 64)? 0 : (r * 100) / 63;
    		return left | (right << 8);
	}

	if (preg)
		ess_setmixer(sc, preg, (l << 4) | r);
	if (rreg)
		ess_setmixer(sc, rreg, (l << 4) | r);

	left = (l * 100) / 15;
	right = (r * 100) / 15;

    	return left | (right << 8);
}