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
typedef  int u_int32_t ;
typedef  int u_char ;
struct snd_mixer {int dummy; } ;
struct sb_info {int dummy; } ;

/* Variables and functions */
 int SB16_IMASK_L ; 
 int SB16_IMASK_R ; 
 int SB16_OMASK ; 
 int SOUND_MASK_CD ; 
 int SOUND_MASK_LINE ; 
 int SOUND_MASK_LINE1 ; 
 int SOUND_MASK_MIC ; 
 int SOUND_MASK_SYNTH ; 
 struct sb_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  sb_setmixer (struct sb_info*,int,int) ; 

__attribute__((used)) static u_int32_t
sb16mix_setrecsrc(struct snd_mixer *m, u_int32_t src)
{
    	struct sb_info *sb = mix_getdevinfo(m);
    	u_char recdev_l, recdev_r;

	recdev_l = 0;
	recdev_r = 0;
	if (src & SOUND_MASK_MIC) {
		recdev_l |= 0x01; /* mono mic */
		recdev_r |= 0x01;
	}

	if (src & SOUND_MASK_CD) {
		recdev_l |= 0x04; /* l cd */
		recdev_r |= 0x02; /* r cd */
	}

	if (src & SOUND_MASK_LINE) {
		recdev_l |= 0x10; /* l line */
		recdev_r |= 0x08; /* r line */
	}

	if (src & SOUND_MASK_SYNTH) {
		recdev_l |= 0x40; /* l midi */
		recdev_r |= 0x20; /* r midi */
	}

	sb_setmixer(sb, SB16_IMASK_L, recdev_l);
	sb_setmixer(sb, SB16_IMASK_R, recdev_r);

	/* Switch on/off FM tuner source */
	if (src & SOUND_MASK_LINE1)
		sb_setmixer(sb, 0x4a, 0x0c);
	else
		sb_setmixer(sb, 0x4a, 0x00);

	/*
	 * since the same volume controls apply to the input and
	 * output sections, the best approach to have a consistent
	 * behaviour among cards would be to disable the output path
	 * on devices which are used to record.
	 * However, since users like to have feedback, we only disable
	 * the mic -- permanently.
	 */
        sb_setmixer(sb, SB16_OMASK, 0x1f & ~1);

	return src;
}