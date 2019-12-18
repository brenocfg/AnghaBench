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
struct snd_mixer {int /*<<< orphan*/  hwvol_mixer; int /*<<< orphan*/  hwvol_mute_level; scalar_t__ hwvol_muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  mixer_get (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_set (struct snd_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mixer_hwvol_mute_locked(struct snd_mixer *m)
{
	if (m->hwvol_muted) {
		m->hwvol_muted = 0;
		mixer_set(m, m->hwvol_mixer, m->hwvol_mute_level);
	} else {
		m->hwvol_muted++;
		m->hwvol_mute_level = mixer_get(m, m->hwvol_mixer);
		mixer_set(m, m->hwvol_mixer, 0);
	}
}