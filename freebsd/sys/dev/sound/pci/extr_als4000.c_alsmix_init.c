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
struct TYPE_2__ {scalar_t__ iselect; scalar_t__ bits; } ;

/* Variables and functions */
 size_t SOUND_MIXER_NRDEVICES ; 
 TYPE_1__* amt ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,size_t) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,size_t) ; 

__attribute__((used)) static int
alsmix_init(struct snd_mixer *m)
{
	u_int32_t i, v;

	for (i = v = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if (amt[i].bits) v |= 1 << i;
	}
	mix_setdevs(m, v);

	for (i = v = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if (amt[i].iselect) v |= 1 << i;
	}
	mix_setrecdevs(m, v);
	return 0;
}