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
 int ac97_reinitmixer (struct ac97_info*) ; 
 struct ac97_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static int
ac97mix_reinit(struct snd_mixer *m)
{
	struct ac97_info *codec = mix_getdevinfo(m);

	if (codec == NULL)
		return -1;
	return ac97_reinitmixer(codec);
}