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
struct sb_info {int dummy; } ;

/* Variables and functions */
 int SOUND_MASK_CD ; 
 int SOUND_MASK_LINE ; 
 int SOUND_MASK_MIC ; 
 int SOUND_MASK_PCM ; 
 int SOUND_MASK_SYNTH ; 
 int SOUND_MASK_VOLUME ; 
 struct sb_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  sb_setmixer (struct sb_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sbpromix_init(struct snd_mixer *m)
{
    	struct sb_info *sb = mix_getdevinfo(m);

	mix_setdevs(m, SOUND_MASK_SYNTH | SOUND_MASK_PCM | SOUND_MASK_LINE |
		       SOUND_MASK_MIC | SOUND_MASK_CD | SOUND_MASK_VOLUME);

	mix_setrecdevs(m, SOUND_MASK_LINE | SOUND_MASK_MIC | SOUND_MASK_CD);

	sb_setmixer(sb, 0, 1); /* reset mixer */

    	return 0;
}