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
struct ac97_info {int dummy; } ;

/* Variables and functions */
 unsigned int AC97_MIXER_SIZE ; 
 int ac97_setmixer (struct ac97_info*,unsigned int,unsigned int,unsigned int) ; 
 struct ac97_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static int
ac97mix_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct ac97_info *codec = mix_getdevinfo(m);

	if (codec == NULL || dev >= AC97_MIXER_SIZE)
		return -1;
	return ac97_setmixer(codec, dev, left, right);
}