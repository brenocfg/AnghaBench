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
typedef  int u_short ;
struct snd_mixer {int dummy; } ;
struct ad1816_info {int dummy; } ;

/* Variables and functions */
 unsigned int AD1816_MUTE ; 
#define  SOUND_MIXER_CD 136 
#define  SOUND_MIXER_IGAIN 135 
#define  SOUND_MIXER_LINE 134 
#define  SOUND_MIXER_LINE1 133 
#define  SOUND_MIXER_LINE3 132 
#define  SOUND_MIXER_MIC 131 
#define  SOUND_MIXER_PCM 130 
#define  SOUND_MIXER_SYNTH 129 
#define  SOUND_MIXER_VOLUME 128 
 int /*<<< orphan*/  ad1816_lock (struct ad1816_info*) ; 
 int ad1816_read (struct ad1816_info*,int) ; 
 int /*<<< orphan*/  ad1816_unlock (struct ad1816_info*) ; 
 int /*<<< orphan*/  ad1816_write (struct ad1816_info*,int,int) ; 
 struct ad1816_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ad1816mix_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct ad1816_info *ad1816 = mix_getdevinfo(m);
    	u_short reg = 0;

    	/* Scale volumes */
    	left = AD1816_MUTE - (AD1816_MUTE * left) / 100;
    	right = AD1816_MUTE - (AD1816_MUTE * right) / 100;

    	reg = (left << 8) | right;

    	/* do channel selective muting if volume is zero */
    	if (left == AD1816_MUTE)	reg |= 0x8000;
    	if (right == AD1816_MUTE)	reg |= 0x0080;

	ad1816_lock(ad1816);
    	switch (dev) {
    	case SOUND_MIXER_VOLUME:	/* Register 14 master volume */
		ad1816_write(ad1816, 14, reg);
		break;

    	case SOUND_MIXER_CD:	/* Register 15 cd */
    	case SOUND_MIXER_LINE1:
		ad1816_write(ad1816, 15, reg);
		break;

    	case SOUND_MIXER_SYNTH:	/* Register 16 synth */
		ad1816_write(ad1816, 16, reg);
		break;

    	case SOUND_MIXER_PCM:	/* Register 4 pcm */
		ad1816_write(ad1816, 4, reg);
		break;

    	case SOUND_MIXER_LINE:
    	case SOUND_MIXER_LINE3:	/* Register 18 line in */
		ad1816_write(ad1816, 18, reg);
		break;

    	case SOUND_MIXER_MIC:	/* Register 19 mic volume */
		ad1816_write(ad1816, 19, reg & ~0xff);	/* mic is mono */
		break;

    	case SOUND_MIXER_IGAIN:
		/* and now to something completely different ... */
		ad1816_write(ad1816, 20, ((ad1816_read(ad1816, 20) & ~0x0f0f)
	      	| (((AD1816_MUTE - left) / 2) << 8) /* four bits of adc gain */
	      	| ((AD1816_MUTE - right) / 2)));
		break;

    	default:
		printf("ad1816_mixer_set(): unknown device.\n");
		break;
    	}
	ad1816_unlock(ad1816);

    	left = ((AD1816_MUTE - left) * 100) / AD1816_MUTE;
    	right = ((AD1816_MUTE - right) * 100) / AD1816_MUTE;

    	return left | (right << 8);
}