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
typedef  int u_int8_t ;
typedef  size_t u_int32_t ;
struct sc_info {int dummy; } ;
typedef  int int32_t ;
struct TYPE_2__ {size_t max; size_t reg; scalar_t__ mute; scalar_t__ neg; } ;

/* Variables and functions */
 int SV_MUTE ; 
 TYPE_1__* mt ; 
 int sv_indirect_get (struct sc_info*,size_t) ; 
 int /*<<< orphan*/  sv_indirect_set (struct sc_info*,size_t,int) ; 

__attribute__((used)) static void
sv_channel_gain(struct sc_info *sc, u_int32_t dev, u_int32_t gain, u_int32_t channel)
{
	u_int8_t	v;
	int32_t		g;

	g = mt[dev].max * gain / 100;
	if (mt[dev].neg)
		g = mt[dev].max - g;
	v  = sv_indirect_get(sc, mt[dev].reg + channel) & ~mt[dev].max;
	v |= g;

	if (mt[dev].mute) {
		if (gain == 0) {
			v |= SV_MUTE;
		} else {
			v &= ~SV_MUTE;
		}
	}
	sv_indirect_set(sc, mt[dev].reg + channel, v);
}