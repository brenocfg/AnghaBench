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
struct sc_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24HT_MIX_MASK ; 
 int /*<<< orphan*/  ENVY24HT_MIX_REC_MASK ; 
 int /*<<< orphan*/  ENVY24HT_MT_VOLRATE ; 
 int SD_F_SOFTPCMVOL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  envy24ht_wrmt (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 struct sc_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
envy24htmixer_init(struct snd_mixer *m)
{
	struct sc_info *sc = mix_getdevinfo(m);

#if(0)
	device_printf(sc->dev, "envy24htmixer_init()\n");
#endif
	if (sc == NULL)
		return -1;

	/* set volume control rate */
	snd_mtxlock(sc->lock);
#if 0
	envy24ht_wrmt(sc, ENVY24HT_MT_VOLRATE, 0x30, 1); /* 0x30 is default value */
#endif

	pcm_setflags(sc->dev, pcm_getflags(sc->dev) | SD_F_SOFTPCMVOL);

	mix_setdevs(m, ENVY24HT_MIX_MASK);
	mix_setrecdevs(m, ENVY24HT_MIX_REC_MASK);
	
	snd_mtxunlock(sc->lock);

	return 0;
}