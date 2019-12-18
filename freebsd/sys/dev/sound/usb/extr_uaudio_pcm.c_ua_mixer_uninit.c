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

/* Variables and functions */
 int /*<<< orphan*/  mix_getdevinfo (struct snd_mixer*) ; 
 int uaudio_mixer_uninit_sub (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ua_mixer_uninit(struct snd_mixer *m)
{
	return (uaudio_mixer_uninit_sub(mix_getdevinfo(m)));
}