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
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  SCREAMER_CODEC_ADDR2 ; 
 int /*<<< orphan*/  SCREAMER_CODEC_ADDR4 ; 
#define  SOUND_MIXER_VOLUME 128 
 struct davbus_softc* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screamer_write_locked (struct davbus_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
screamer_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
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
		screamer_write_locked(d, SCREAMER_CODEC_ADDR2, (lval << 6) |
		    rval);
		screamer_write_locked(d, SCREAMER_CODEC_ADDR4, (lval << 6) | 
		    rval);
		mtx_unlock(&d->mutex);

		return (left | (right << 8));
	}

	return (0);
}