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
typedef  int u_int32_t ;
struct snd_mixer {int dummy; } ;
struct sc_info {int dummy; } ;
struct TYPE_2__ {int iselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB16_IMASK_L ; 
 int /*<<< orphan*/  SB16_IMASK_R ; 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  als_mix_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* amt ; 
 struct sc_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static u_int32_t
alsmix_setrecsrc(struct snd_mixer *m, u_int32_t src)
{
	struct sc_info *sc = mix_getdevinfo(m);
	u_int32_t i, l, r;

	for (i = l = r = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if (src & (1 << i)) {
			if (amt[i].iselect == 1) {	/* microphone */
				l |= amt[i].iselect;
				r |= amt[i].iselect;
			} else {
				l |= amt[i].iselect;
				r |= amt[i].iselect >> 1;
			}
		}
	}

	als_mix_wr(sc, SB16_IMASK_L, l);
	als_mix_wr(sc, SB16_IMASK_R, r);
	return src;
}