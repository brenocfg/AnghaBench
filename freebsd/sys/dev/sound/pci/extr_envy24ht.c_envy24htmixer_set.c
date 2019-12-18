#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_mixer {int dummy; } ;
struct sc_info {int dacn; scalar_t__* left; scalar_t__* right; int /*<<< orphan*/  lock; TYPE_3__* chan; int /*<<< orphan*/ * dac; TYPE_2__* cfg; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ run; } ;
struct TYPE_5__ {TYPE_1__* codec; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* setvolume ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int ENVY24HT_CHAN_PLAY_SPDIF ; 
 scalar_t__ ENVY24HT_VOL_MIN ; 
 void* ENVY24HT_VOL_MUTE ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 int* envy24ht_chanmap ; 
 int* envy24ht_mixmap ; 
 int /*<<< orphan*/  envy24ht_setvolume (struct sc_info*,int) ; 
 struct sc_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int
envy24htmixer_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct sc_info *sc = mix_getdevinfo(m);
	int ch = envy24ht_mixmap[dev];
	int hwch;
	int i;

	if (sc == NULL)
		return -1;
	if (dev == 0 && sc->cfg->codec->setvolume == NULL)
		return -1;
	if (dev != 0 && ch == -1)
		return -1;
	hwch = envy24ht_chanmap[ch];
#if(0)
	device_printf(sc->dev, "envy24htmixer_set(m, %d, %d, %d)\n",
	    dev, left, right);
#endif

	snd_mtxlock(sc->lock);
	if (dev == 0) {
		for (i = 0; i < sc->dacn; i++) {
			sc->cfg->codec->setvolume(sc->dac[i], PCMDIR_PLAY, left, right);
		}
	}
	else {
		/* set volume value for hardware */
		if ((sc->left[hwch] = 100 - left) > ENVY24HT_VOL_MIN)
			sc->left[hwch] = ENVY24HT_VOL_MUTE;
		if ((sc->right[hwch] = 100 - right) > ENVY24HT_VOL_MIN)
			sc->right[hwch] = ENVY24HT_VOL_MUTE;

		/* set volume for record channel and running play channel */
		if (hwch > ENVY24HT_CHAN_PLAY_SPDIF || sc->chan[ch].run)
			envy24ht_setvolume(sc, hwch);
	}
	snd_mtxunlock(sc->lock);

	return right << 8 | left;
}