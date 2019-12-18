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
struct snd_mixer {int hwvol_mute_level; int hwvol_step; int /*<<< orphan*/  hwvol_mixer; scalar_t__ hwvol_muted; } ;

/* Variables and functions */
 int mixer_get (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_set (struct snd_mixer*,int /*<<< orphan*/ ,int) ; 

void
mixer_hwvol_step_locked(struct snd_mixer *m, int left_step, int right_step)
{
	int level, left, right;

	if (m->hwvol_muted) {
		m->hwvol_muted = 0;
		level = m->hwvol_mute_level;
	} else
		level = mixer_get(m, m->hwvol_mixer);
	if (level != -1) {
		left = level & 0xff;
		right = (level >> 8) & 0xff;
		left += left_step * m->hwvol_step;
		if (left < 0)
			left = 0;
		else if (left > 100)
			left = 100;
		right += right_step * m->hwvol_step;
		if (right < 0)
			right = 0;
		else if (right > 100)
			right = 100;
		mixer_set(m, m->hwvol_mixer, left | right << 8);
	}
}