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
typedef  int u_int32_t ;
struct snd_mixer {int* parent; int* child; } ;

/* Variables and functions */
 int SOUND_MIXER_NRDEVICES ; 

void
mix_setparentchild(struct snd_mixer *m, u_int32_t parent, u_int32_t childs)
{
	u_int32_t mask = 0;
	int i;

	if (m == NULL || parent >= SOUND_MIXER_NRDEVICES)
		return;
	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if (i == parent)
			continue;
		if (childs & (1 << i)) {
			mask |= 1 << i;
			if (m->parent[i] < SOUND_MIXER_NRDEVICES)
				m->child[m->parent[i]] &= ~(1 << i);
			m->parent[i] = parent;
			m->child[i] = 0;
		}
	}
	mask &= ~(1 << parent);
	m->child[parent] = mask;
}