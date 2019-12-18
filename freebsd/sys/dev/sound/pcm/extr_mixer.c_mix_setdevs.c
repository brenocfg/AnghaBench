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
struct snddev_info {int flags; } ;
struct snd_mixer {int* parent; int* child; int devs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SD_F_EQ ; 
 int SD_F_SOFTPCMVOL ; 
 int SOUND_MASK_BASS ; 
 int SOUND_MASK_PCM ; 
 int SOUND_MASK_TREBLE ; 
 int SOUND_MIXER_NRDEVICES ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 

void
mix_setdevs(struct snd_mixer *m, u_int32_t v)
{
	struct snddev_info *d;
	int i;

	if (m == NULL)
		return;

	d = device_get_softc(m->dev);
	if (d != NULL && (d->flags & SD_F_SOFTPCMVOL))
		v |= SOUND_MASK_PCM;
	if (d != NULL && (d->flags & SD_F_EQ))
		v |= SOUND_MASK_TREBLE | SOUND_MASK_BASS;
	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if (m->parent[i] < SOUND_MIXER_NRDEVICES)
			v |= 1 << m->parent[i];
		v |= m->child[i];
	}
	m->devs = v;
}