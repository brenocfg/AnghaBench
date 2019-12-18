#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct snd_mixer {int dummy; } ;
struct a10codec_info {int dummy; } ;
struct TYPE_2__ {unsigned int mask; unsigned int shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int CODEC_READ (struct a10codec_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODEC_WRITE (struct a10codec_info*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* a10_mixers ; 
 struct a10codec_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static int
a10_mixer_set(struct snd_mixer *m, unsigned dev, unsigned left,
    unsigned right)
{
	struct a10codec_info *sc = mix_getdevinfo(m);
	uint32_t val;
	unsigned nvol, max;

	max = a10_mixers[dev].mask >> a10_mixers[dev].shift;
	nvol = (left * max) / 100;

	val = CODEC_READ(sc, a10_mixers[dev].reg);
	val &= ~a10_mixers[dev].mask;
	val |= (nvol << a10_mixers[dev].shift);
	CODEC_WRITE(sc, a10_mixers[dev].reg, val);

	left = right = (left * 100) / max;
	return (left | (right << 8));
}