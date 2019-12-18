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
struct sc_info {int dummy; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 size_t SOUND_MIXER_NRDEVICES ; 
 TYPE_1__* mt ; 
 int /*<<< orphan*/  sv_gain (struct sc_info*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sv_mix_mute_all(struct sc_info *sc)
{
	int32_t i;
	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		if (mt[i].reg) sv_gain(sc, i, 0, 0);
	}
}