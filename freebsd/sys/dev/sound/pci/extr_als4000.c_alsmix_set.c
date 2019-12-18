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
typedef  unsigned int u_int32_t ;
struct snd_mixer {int dummy; } ;
struct sc_info {int dummy; } ;
struct TYPE_2__ {int bits; unsigned int oselect; scalar_t__ rreg; scalar_t__ lreg; } ;

/* Variables and functions */
 scalar_t__ SB16_OMASK ; 
 unsigned int als_mix_rd (struct sc_info*,scalar_t__) ; 
 int /*<<< orphan*/  als_mix_wr (struct sc_info*,scalar_t__,unsigned int) ; 
 TYPE_1__* amt ; 
 struct sc_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static int
alsmix_set(struct snd_mixer *m, unsigned dev, unsigned left, unsigned right)
{
	struct sc_info *sc = mix_getdevinfo(m);
	u_int32_t r, l, v, mask;

	/* Fill upper n bits in mask with 1's */
	mask = ((1 << amt[dev].bits) - 1) << (8 - amt[dev].bits);

	l = (left * mask / 100) & mask;
	v = als_mix_rd(sc, amt[dev].lreg) & ~mask;
	als_mix_wr(sc, amt[dev].lreg, l | v);

	if (amt[dev].rreg) {
		r = (right * mask / 100) & mask;
		v = als_mix_rd(sc, amt[dev].rreg) & ~mask;
		als_mix_wr(sc, amt[dev].rreg, r | v);
	} else {
		r = 0;
	}

	/* Zero gain does not mute channel from output, but this does. */
	v = als_mix_rd(sc, SB16_OMASK);
	if (l == 0 && r == 0) {
		v &= ~amt[dev].oselect;
	} else {
		v |= amt[dev].oselect;
	}
	als_mix_wr(sc, SB16_OMASK, v);
	return 0;
}