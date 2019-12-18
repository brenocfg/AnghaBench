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
typedef  int u_int ;
typedef  int u_char ;
struct tumbler_softc {int dummy; } ;
struct snd_mixer {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
#define  SOUND_MIXER_VOLUME 128 
 int /*<<< orphan*/  TUMBLER_VOLUME ; 
 struct tumbler_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_getdevinfo (struct snd_mixer*) ; 
 struct mtx* mixer_get_lock (struct snd_mixer*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int mtx_owned (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int* tumbler_volume_table ; 
 int /*<<< orphan*/  tumbler_write (struct tumbler_softc*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
tumbler_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct tumbler_softc *sc;
	struct mtx *mixer_lock;
	int locked;
	u_int l, r;
	u_char reg[6];

	sc = device_get_softc(mix_getdevinfo(m));
	mixer_lock = mixer_get_lock(m);
	locked = mtx_owned(mixer_lock);

	switch (dev) {
	case SOUND_MIXER_VOLUME:
		if (left > 100 || right > 100)
			return (0);

		l = (left == 0 ? 0 : tumbler_volume_table[left - 1]);
		r = (right == 0 ? 0 : tumbler_volume_table[right - 1]);
		
		reg[0] = (l & 0xff0000) >> 16;
		reg[1] = (l & 0x00ff00) >> 8;
		reg[2] = l & 0x0000ff;
		reg[3] = (r & 0xff0000) >> 16;
		reg[4] = (r & 0x00ff00) >> 8;
		reg[5] = r & 0x0000ff;

		/*
		 * We need to unlock the mixer lock because iicbus_transfer()
		 * may sleep. The mixer lock itself is unnecessary here
		 * because it is meant to serialize hardware access, which
		 * is taken care of by the I2C layer, so this is safe.
		 */

		if (locked)
			mtx_unlock(mixer_lock);

		tumbler_write(sc, TUMBLER_VOLUME, reg);

		if (locked)
			mtx_lock(mixer_lock);

		return (left | (right << 8));
	}

	return (0);
}