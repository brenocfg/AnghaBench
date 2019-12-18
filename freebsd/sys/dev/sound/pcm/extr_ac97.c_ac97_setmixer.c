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
struct ac97mixtable_entry {int reg; int enable; int bits; int ofs; int mute; scalar_t__ mask; int /*<<< orphan*/  stereo; } ;
struct ac97_info {int /*<<< orphan*/  lock; struct ac97mixtable_entry* mix; } ;

/* Variables and functions */
 int AC97_MUTE ; 
 int ac97_rdcd (struct ac97_info*,int) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ac97_setmixer(struct ac97_info *codec, unsigned channel, unsigned left, unsigned right)
{
	struct ac97mixtable_entry *e = &codec->mix[channel];

	if (e->reg && e->enable && e->bits) {
		int mask, max, val, reg;

		reg = (e->reg >= 0) ? e->reg : -e->reg;	/* AC97 register    */
		max = (1 << e->bits) - 1;		/* actual range	    */
		mask = (max << 8) | max;		/* bits of interest */

		if (!e->stereo)
			right = left;

		/*
		 * Invert the range if the polarity requires so,
		 * then scale to 0..max-1 to compute the value to
		 * write into the codec, and scale back to 0..100
		 * for the return value.
		 */
		if (e->reg > 0) {
			left = 100 - left;
			right = 100 - right;
		}

		left = (left * max) / 100;
		right = (right * max) / 100;

		val = (left << 8) | right;

		left = (left * 100) / max;
		right = (right * 100) / max;

		if (e->reg > 0) {
			left = 100 - left;
			right = 100 - right;
		}

		/*
		 * For mono controls, trim val and mask, also taking
		 * care of e->ofs (offset of control field).
		 */
		if (e->ofs) {
			val &= max;
			val <<= e->ofs;
			mask = (max << e->ofs);
		}

		/*
		 * If we have a mute bit, add it to the mask and
		 * update val and set mute if both channels require a
		 * zero volume.
		 */
		if (e->mute == 1) {
			mask |= AC97_MUTE;
			if (left == 0 && right == 0)
				val = AC97_MUTE;
		}

		/*
		 * If the mask bit is set, do not alter the other bits.
		 */
		snd_mtxlock(codec->lock);
		if (e->mask) {
			int cur = ac97_rdcd(codec, reg);
			val |= cur & ~(mask);
		}
		ac97_wrcd(codec, reg, val);
		snd_mtxunlock(codec->lock);
		return left | (right << 8);
	} else {
#if 0
		printf("ac97_setmixer: reg=%d, bits=%d, enable=%d\n", e->reg, e->bits, e->enable);
#endif
		return -1;
	}
}