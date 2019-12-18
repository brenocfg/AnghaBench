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
struct snd_mixer {int recdevs; } ;

/* Variables and functions */
 int EINVAL ; 
 int SOUND_MIXER_NRDEVICES ; 
 int mixer_setrecsrc (struct snd_mixer*,int) ; 

__attribute__((used)) static int
mixer_set_recroute(struct snd_mixer *m, int route)
{
	int i, cnt, ret;

	ret = 0;
	cnt = 0;

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if ((1 << i) & m->recdevs) {
			if (route == cnt)
				break;
			++cnt;
		}
	}

	if (i == SOUND_MIXER_NRDEVICES)
		ret = EINVAL;
	else
		ret = mixer_setrecsrc(m, (1 << i));

	return ret;
}