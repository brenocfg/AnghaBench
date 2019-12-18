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
struct sc_pchinfo {int fmt; scalar_t__ spd; struct emu_voice* master; } ;
struct emu_voice {int b16; int stereo; scalar_t__ speed; TYPE_1__* slave; } ;
struct TYPE_2__ {int b16; int stereo; scalar_t__ speed; } ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_CHANNEL (int) ; 

__attribute__((used)) static void
emu_vsetup(struct sc_pchinfo *ch)
{
	struct emu_voice *v = ch->master;

	if (ch->fmt) {
		v->b16 = (ch->fmt & AFMT_16BIT) ? 1 : 0;
		v->stereo = (AFMT_CHANNEL(ch->fmt) > 1) ? 1 : 0;
		if (v->slave != NULL) {
			v->slave->b16 = v->b16;
			v->slave->stereo = v->stereo;
		}
	}
	if (ch->spd) {
		v->speed = ch->spd;
		if (v->slave != NULL)
			v->slave->speed = v->speed;
	}
}