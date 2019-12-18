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
struct snd_mixer {int recsrc; int recdevs; } ;

/* Variables and functions */
 int EIDRM ; 
 int SOUND_MIXER_NRDEVICES ; 

__attribute__((used)) static int
mixer_get_recroute(struct snd_mixer *m, int *route)
{
	int i, cnt;

	cnt = 0;

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		/** @todo can user set a multi-device mask? (== or &?) */
		if ((1 << i) == m->recsrc)
			break;
		if ((1 << i) & m->recdevs)
			++cnt;
	}

	if (i == SOUND_MIXER_NRDEVICES)
		return EIDRM;

	*route = cnt;
	return 0;
}