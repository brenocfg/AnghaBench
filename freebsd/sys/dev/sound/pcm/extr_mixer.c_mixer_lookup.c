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

/* Variables and functions */
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/ * snd_mixernames ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mixer_lookup(char *devname)
{
	int i;

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
		if (strncmp(devname, snd_mixernames[i],
		    strlen(snd_mixernames[i])) == 0)
			return i;
	return -1;
}