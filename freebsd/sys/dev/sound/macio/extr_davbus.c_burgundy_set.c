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
struct davbus_softc {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BURGUNDY_OL13_REG ; 
 int /*<<< orphan*/  BURGUNDY_OL14_REG ; 
 int /*<<< orphan*/  BURGUNDY_OL15_REG ; 
 int /*<<< orphan*/  BURGUNDY_OL16_REG ; 
 int /*<<< orphan*/  BURGUNDY_OL17_REG ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
#define  SOUND_MIXER_VOLUME 128 
 int /*<<< orphan*/  burgundy_write_locked (struct davbus_softc*,int /*<<< orphan*/ ,int) ; 
 struct davbus_softc* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
burgundy_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct davbus_softc *d;
	int lval, rval;

	lval = ((100 - left) * 15 / 100) & 0xf;
	rval = ((100 - right) * 15 / 100) & 0xf;
	DPRINTF(("volume %d %d\n", lval, rval));

	d = mix_getdevinfo(m);

	switch (dev) {
	case SOUND_MIXER_VOLUME:
		mtx_lock(&d->mutex);

		burgundy_write_locked(d, BURGUNDY_OL13_REG, lval);
		burgundy_write_locked(d, BURGUNDY_OL14_REG, (rval << 4) | lval);
		burgundy_write_locked(d, BURGUNDY_OL15_REG, (rval << 4) | lval);
		burgundy_write_locked(d, BURGUNDY_OL16_REG, (rval << 4) | lval);
		burgundy_write_locked(d, BURGUNDY_OL17_REG, lval);

		mtx_unlock(&d->mutex);

		return (left | (right << 8));
	}

	return (0);
}