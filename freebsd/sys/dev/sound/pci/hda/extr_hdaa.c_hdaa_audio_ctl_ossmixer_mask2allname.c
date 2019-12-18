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
typedef  int uint32_t ;

/* Variables and functions */
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 char** ossnames ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static char *
hdaa_audio_ctl_ossmixer_mask2allname(uint32_t mask, char *buf, size_t len)
{
	int i, first = 1;

	bzero(buf, len);
	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if (mask & (1 << i)) {
			if (first == 0)
				strlcat(buf, ", ", len);
			strlcat(buf, ossnames[i], len);
			first = 0;
		}
	}
	return (buf);
}