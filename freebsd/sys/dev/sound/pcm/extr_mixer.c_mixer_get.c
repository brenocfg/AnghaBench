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
struct snd_mixer {int devs; int* level; } ;

/* Variables and functions */
 int SOUND_MIXER_NRDEVICES ; 

__attribute__((used)) static int
mixer_get(struct snd_mixer *mixer, int dev)
{
	if ((dev < SOUND_MIXER_NRDEVICES) && (mixer->devs & (1 << dev)))
		return mixer->level[dev];
	else
		return -1;
}