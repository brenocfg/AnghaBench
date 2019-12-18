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
struct emu_pcm_info {int /*<<< orphan*/ * sm; } ;

/* Variables and functions */
 struct emu_pcm_info* mix_getdevinfo (struct snd_mixer*) ; 
 int mixer_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
emu_dspmixer_uninit(struct snd_mixer *m)
{
	struct emu_pcm_info	*sc;
	int err = 0;

	/* drop submixer for AC97 codec */
	sc = mix_getdevinfo(m);
	if (sc->sm != NULL)
		err = mixer_delete(sc->sm);
		if (err)
			return (err);
		sc->sm = NULL;
	return (0);
}