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
 int /*<<< orphan*/  ENVY24_MIX_MASK ; 
 int /*<<< orphan*/  ENVY24_MIX_REC_MASK ; 
 int /*<<< orphan*/  ENVY24_MT_VOLRATE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  envy24_wrmt (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 struct sc_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
envy24mixer_init(struct snd_mixer *m)
{
	struct sc_info *sc = mix_getdevinfo(m);

#if(0)
	device_printf(sc->dev, "envy24mixer_init()\n");
#endif
	if (sc == NULL)
		return -1;

	/* set volume control rate */
	snd_mtxlock(sc->lock);
	envy24_wrmt(sc, ENVY24_MT_VOLRATE, 0x30, 1); /* 0x30 is default value */

	mix_setdevs(m, ENVY24_MIX_MASK);
	mix_setrecdevs(m, ENVY24_MIX_REC_MASK);
	snd_mtxunlock(sc->lock);

	return 0;
}