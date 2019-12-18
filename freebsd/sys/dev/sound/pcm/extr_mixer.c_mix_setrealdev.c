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
typedef  scalar_t__ u_int32_t ;
struct snd_mixer {scalar_t__* realdev; } ;

/* Variables and functions */
 scalar_t__ SOUND_MIXER_NONE ; 
 scalar_t__ SOUND_MIXER_NRDEVICES ; 

void
mix_setrealdev(struct snd_mixer *m, u_int32_t dev, u_int32_t realdev)
{
	if (m == NULL || dev >= SOUND_MIXER_NRDEVICES ||
	    !(realdev == SOUND_MIXER_NONE || realdev < SOUND_MIXER_NRDEVICES))
		return;
	m->realdev[dev] = realdev;
}